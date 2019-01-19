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

        public Inporter inputer;

        public List<Vector3> listOfPoints = new List<Vector3>();
        public GameObject loadedObject;
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
            _netMqListener = new NetMqListener(ListenMessage);
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
        private void ListenMessage(string message)
        {
            if(message != null)
            {
                inputer.SetPoints(message);
            }

            //if(message != null)
            //{
            //    Debug.Log("recived message: " + message);
            //    var splittedMessage = message.Split('\n');
            //    for (var i = 1; i < splittedMessage.Length; i++)
            //    {
            //        var splittedPoint = splittedMessage[i].Split(' ');
            //        Debug.Log("Splitted point dimension: " + splittedPoint.Length);
            //        var x = float.Parse(splittedPoint[0]);
            //        var y = float.Parse(splittedPoint[1]);
            //        var z = float.Parse(splittedPoint[2]);
            //        listOfPoints.Add(new Vector3(x, y, z));
            //    }

            //    Mesh pointMesh = new Mesh();
            //    pointMesh.SetVertices(listOfPoints);
            //    pointMesh.RecalculateBounds();
            //    this.loadedObject.GetComponent<MeshFilter>().mesh = pointMesh;
            //    Material material = new Material(Resources.Load<Shader>("GeometryShader"));
            //    material.SetFloat("_Size", 1);
            //    material.SetColor("_Color", Color.cyan);
            //    this.loadedObject.GetComponent<MeshRenderer>().material = material;
            //}
            
        }
    }
}

