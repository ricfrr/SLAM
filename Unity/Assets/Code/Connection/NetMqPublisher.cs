using System.Diagnostics;
using System.Threading;
using System.IO;
using NetMQ;
using NetMQ.Sockets;
using Assets.Code.Structs;
using System.Collections.Generic;
using UnityEngine;
using System.Text;

namespace Assets.Code.Connection
{
    public class NetMqPublisher
    {
        private readonly Thread _listenerWorker;
        private bool _listenerCancelled, _isSending;
        public delegate string MessageDelegate(string message);
        private readonly MessageDelegate _messageDelegate;
        private readonly Stopwatch _contactWatch;
        private const long ContactThreshold = 1000;
        public bool Connected;

        private Vector3[] toSend;

        public NetMqPublisher(MessageDelegate messageDelegate)
        {
            _messageDelegate = messageDelegate;
            _contactWatch = new Stopwatch();
            _contactWatch.Start();
            _listenerWorker = new Thread(ListenerWork);
        }

        public void Start()
        {
            _listenerCancelled = false;
            _isSending = false;
            _listenerWorker.Start();
        }

        public void Stop()
        {
            _listenerCancelled = true;
            _listenerWorker.Join();
        }

        public void refreshPoint(Vector3[] capturedPoints)
        {
            this.toSend = capturedPoints;
            _isSending = true;
        }

        private void ListenerWork()
        {
            AsyncIO.ForceDotNet.Force();
            using (var server = new PublisherSocket())
            {
                server.Options.SendHighWatermark = 1000;
                server.Bind("tcp://localhost:12347");
                UnityEngine.Debug.Log("connected");
                StringBuilder sb;

                int i = 0;
                while (!_listenerCancelled)
                {
                    if(_isSending)
                    {
                        sb = new StringBuilder(i.ToString()).Append("\n");
                        foreach (Vector3 element in this.toSend)
                        {
                            sb.Append(element.x).Append(" ").Append(element.y).Append(" ").Append(element.z).Append("\n");
                            // normal concatenation does NOT work - unity freez
                            //message +=  + " " + element.y + " " + element.z + "\n";
                        }
                        server.SendFrame(sb.ToString());
                        i++;
                        UnityEngine.Debug.Log("sent");
                        _isSending = false;
                    }
                    Thread.Sleep(1000);
                }
            }
            
        }
    }
}