using UnityEngine;
using System.Collections;
using Assets.Code.Connection;

namespace Assets.Code.GameObjects
{
    public class Connection : MonoBehaviour
    {
        // server
        public bool Connected;
        private NetMqPublisher _netMqPublisher;
        private string _response;
        // client
        private NetMqListener _netMqListener;

        // Use this for initialization
        void Start()
        {
            // server
            _netMqPublisher = new NetMqPublisher(PublisMessage);
            _netMqPublisher.Start();
            // client
            _netMqListener = new NetMqListener(LisenMessage);
            _netMqListener.Start();
        }

        // Update is called once per frame
        void Update()
        {
            // server
            var position = transform.position;
            _response = $"{position.x} {position.y} {position.z}";
            Connected = _netMqPublisher.Connected;
            // client
            _netMqListener.Update();
        }

        private void OnDestroy()
        {
            // server
            _netMqPublisher.Stop();
            // client
            _netMqListener.Stop();
        }

        // server
        private string PublisMessage(string message)
        {
            // Not on main thread
            return _response;
        }

        // client
        private void LisenMessage(string message)
        {
            Debug.Log(message);
            //var splittedStrings = message.Split(' ');
            //if (splittedStrings.Length != 3) return;
            //var x = float.Parse(splittedStrings[0]);
            //var y = float.Parse(splittedStrings[1]);
            //var z = float.Parse(splittedStrings[2]);
            //transform.position = new Vector3(x, y, z);
        }
    }
}

