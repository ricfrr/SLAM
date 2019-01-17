using UnityEngine;
using System.Collections;
using Assets.Code.Connection;
using System.Collections.Generic;
using Assets.Code.Structs;
using NetMQ;

namespace Assets.Code.GameObjects
{
    public class Connection : MonoBehaviour
    {
        // send points
        //public bool Connected;
        private NetMqPublisher _netMqPublisher;
        private string _publisherresponse;
        // send params
        private NetMqSendParams _netMqSendParams;
        private string _paramsresponse;
        // client
        private NetMqListener _netMqListener;
        // reference
        public _3dCamera _3Dcamera;

        private int lastCount;

        // Use this for initialization
        void Start()
        {
            // send points
            _netMqPublisher = new NetMqPublisher(PublisMessage);
            _netMqPublisher.Start();
            // send params
            _netMqSendParams = new NetMqSendParams(Publisparams);
            _netMqSendParams.Start();
            // client
            _netMqListener = new NetMqListener(LisenMessage);
            _netMqListener.Start();

            lastCount = 0;
        }

        // Update is called once per frame
        void Update()
        {
            // send points
            if (this._3Dcamera.GetLastCapturedPoints() != null)
            {
                lastCount++;
                _netMqPublisher.refreshPoint(this._3Dcamera.GetLastCapturedPoints() , this._3Dcamera.GetLastCapturedColors());


            }
            //// send params
            //if (this._3Dcamera.GetLastCapturedPoints() != null)
            //{

            //    _netMqSendParams.pharamToSend("");

            //}
            // client
            _netMqListener.Update();
        }

        private void OnGUI()
        {
            if (GUI.Button(new Rect(Screen.width - 130, Screen.height - 90, 120, 30), "Send pharam"))
            {
                _netMqSendParams.pharamToSend("ALGORITHM\n1");
            }
        }

        private void OnDestroy()
        {
            // send points
            _netMqPublisher.Stop();
            // send pharam
            _netMqSendParams.Stop();
            // client
            _netMqListener.Stop();

            NetMQConfig.Cleanup();
        }

        // send points
        private string PublisMessage(string message)
        {
            // Not on main thread
            return _publisherresponse;
        }

        // send params
        private string Publisparams(string message)
        {
            // Not on main thread
            return _paramsresponse;
        }

        // client
        private void LisenMessage(string message)
        {
            Debug.Log("recived message: "+message);
            //var splittedStrings = message.Split(' ');
            //if (splittedStrings.Length != 3) return;
            //var x = float.Parse(splittedStrings[0]);
            //var y = float.Parse(splittedStrings[1]);
            //var z = float.Parse(splittedStrings[2]);
            //transform.position = new Vector3(x, y, z);
        }
    }
}

