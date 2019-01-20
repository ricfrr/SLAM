using UnityEngine;
using UnityEditor;
using Assets.Code.GameObjects;

namespace Assets.Code.Controllers
{
    public class PlotController : MonoBehaviour
    {
        public GameObjects.Camera plotCamera;

        private Vector3 movment;
        private Vector3 rotation;

        void Update()
        {
            this.cameraTranslationListener();
            this.cameraRotationListener();
        }

        protected void cameraTranslationListener()
        {
            if (Input.GetKey(KeyCode.H))
            {
                this.movment.x += -1;
            }
            if (Input.GetKey(KeyCode.K))
            {
                this.movment.x += 1;
            }
            if (Input.GetKey(KeyCode.Space))
            {
                if (Input.GetKey(KeyCode.U))
                {
                    this.movment.y += 1;
                }
                if (Input.GetKey(KeyCode.J))
                {
                    this.movment.y += -1;
                }
            }
            else
            {
                if (Input.GetKey(KeyCode.U))
                {
                    this.movment.z += 1;
                }
                if (Input.GetKey(KeyCode.J))
                {
                    this.movment.z += -1;
                }
            }

            this.plotCamera.Translate(this.movment);
            this.movment = Vector3.zero;
        }

        protected void cameraRotationListener()
        {
            if (Input.GetKey(KeyCode.UpArrow))
            {
                //needs to be deactivated for the car & activated for the drone
                //this.rotation.x += 1;
            }
            if (Input.GetKey(KeyCode.DownArrow))
            {
                //needs to be deactivated for the car & activated for the drone
                //this.rotation.x += -1;
            }
            if (Input.GetKey(KeyCode.Space))
            {
                if (Input.GetKey(KeyCode.RightArrow))
                {
                    this.rotation.z += -1;
                }
                if (Input.GetKey(KeyCode.LeftArrow))
                {
                    this.rotation.z += 1;
                }
            }
            else
            {
                if (Input.GetKey(KeyCode.RightArrow))
                {
                    this.rotation.y += 3;
                }
                if (Input.GetKey(KeyCode.LeftArrow))
                {
                    this.rotation.y += -3;
                }
            }

            this.plotCamera.Rotate(this.rotation);
            this.rotation = Vector3.zero;
        }
    }
}