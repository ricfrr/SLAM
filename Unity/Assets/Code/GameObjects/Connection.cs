using UnityEngine;
using System.Collections;
using Assets.Code.Connection;
using Assets.Code.Controllers;
using System.Collections.Generic;
using Assets.Code.Structs;
using NetMQ;

namespace Assets.Code.GameObjects
{
    public class Connection : MonoBehaviour
    {
        // server
        private NetMqPublisher _netMqPublisher;
        private string _response;
        // parameters
        private NetMqPCLParams _netMqPCLParams;
        private string _paramsResponse;
        // client
        private NetMqListener _netMqListener;
        // reference
        public _3dCamera _3Dcamera;
        public PclSettingsController pclSettingsCtrl;

        private int lastCount;

        // Use this for initialization
        void Start()
        {
            // server
            _netMqPublisher = new NetMqPublisher(PublisMessage);
            _netMqPublisher.Start();
            // server
            _netMqPCLParams = new NetMqPCLParams(PublisParameter);
            _netMqPCLParams.Start();
            // client
            _netMqListener = new NetMqListener(LisenMessage);
            _netMqListener.Start();

            lastCount = 0;
        }

        // Update is called once per frame
        void Update()
        {
            // server
                    
            if (this._3Dcamera.GetCapturedPointSize() > lastCount)
            {
                lastCount++;
                _netMqPublisher.refreshPoint(this._3Dcamera.GetLastCapturedPoints() , this._3Dcamera.GetLastCapturedColors());
            }
            if (this.pclSettingsCtrl.isParamToSend())
            {
                _netMqPCLParams.sendParams(this.pclSettingsCtrl.GetActualParam());
            }
            // client
            _netMqListener.Update();
        }

        private void OnDestroy()
        {
            // server
            _netMqPublisher.Stop();
            // parameter
            _netMqPCLParams.Stop();
            // client
            _netMqListener.Stop();

            NetMQConfig.Cleanup();
        }

        // server
        private string PublisMessage(string message)
        {
            // Not on main thread
            return _response;
        }

        // parameter
        private string PublisParameter(string parameter)
        {
            // Not on main thread
            return _paramsResponse;
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

