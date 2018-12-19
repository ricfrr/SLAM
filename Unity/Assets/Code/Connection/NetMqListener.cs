using System.Collections.Concurrent;
using System.Threading;
using NetMQ;
using NetMQ.Sockets;
using AsyncIO;
using UnityEngine;

namespace Assets.Code.Connection
{
    public class NetMqListener
    {
        private readonly Thread _listenerWorker;
        private bool _listenerCancelled;
        public delegate void MessageDelegate(string message);
        private readonly MessageDelegate _messageDelegate;
        private readonly ConcurrentQueue<string> _messageQueue = new ConcurrentQueue<string>();

        public NetMqListener(MessageDelegate messageDelegate)
        {
            _messageDelegate = messageDelegate;
            _listenerWorker = new Thread(ListenerWork);
        }

        public void Start()
        {
            _listenerCancelled = false;
            _listenerWorker.Start();
        }

        public void Stop()
        {
            _listenerCancelled = true;
            _listenerWorker.Join();
        }

        public void Update()
        {
            while (!_messageQueue.IsEmpty)
            {
                string message;
                if (_messageQueue.TryDequeue(out message))
                {
                    _messageDelegate(message);
                }
                else
                {
                    break;
                }
            }
        }

        private void ListenerWork()
        {
            AsyncIO.ForceDotNet.Force();
            using (var subSocket = new SubscriberSocket())
            {
                subSocket.Options.ReceiveHighWatermark = 1000;
                subSocket.Connect("tcp://127.0.0.1:12346");
                subSocket.Subscribe("");
                while (!_listenerCancelled)
                {
                    string frameString;
                    if (!subSocket.TryReceiveFrameString(out frameString)) continue;
                    // Debug.Log("recv: "+frameString);
                    _messageQueue.Enqueue(frameString);
                }
                subSocket.Close();
            }
        }
    }
}
