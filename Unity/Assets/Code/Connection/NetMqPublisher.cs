using System.Diagnostics;
using System.Threading;
using System.IO;
using NetMQ;
using NetMQ.Sockets;

namespace Assets.Code.Connection
{
    public class NetMqPublisher
    {
        private readonly Thread _listenerWorker;
        private bool _listenerCancelled;
        public delegate string MessageDelegate(string message);
        private readonly MessageDelegate _messageDelegate;
        private readonly Stopwatch _contactWatch;
        private const long ContactThreshold = 1000;
        public bool Connected;

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
            _listenerWorker.Start();
        }

        public void Stop()
        {
            _listenerCancelled = true;
            _listenerWorker.Join();
        }

        private void ListenerWork()
        {
            AsyncIO.ForceDotNet.Force();
            using (var server = new PublisherSocket())
            {
                server.Options.SendHighWatermark = 1000;
                server.Bind("tcp://127.0.0.1:12347");
                UnityEngine.Debug.Log("connected");

                int i = 0;
                while (!_listenerCancelled)
                {

                    //StreamReader streamReader = new StreamReader("Points_30/(3.4, -15.1, -26.9)(0.0, " + i + ".0, 0.0).pcd");
                    ////this is for skipping the header of pcd and send only points 
                    //for (int k = 0; k < 11; k++)
                    //{
                    //    streamReader.ReadLine();
                    //}

                    //string message = streamReader.ReadToEnd();
                    //UnityEngine.Debug.Log("file readed");
                    //message = i.ToString() + "\n" + message;
                    server.SendFrame("hello\n");
                    UnityEngine.Debug.Log("sent " + i);
                    Thread.Sleep(1000);
                    i++;
                    if (i > 10)
                    {
                        _listenerCancelled = true;
                    }
                }
            }
            NetMQConfig.Cleanup();
        }
    }
}