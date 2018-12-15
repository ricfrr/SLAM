using UnityEngine;
using UnityEditor;
using Assets.Code.GameObjects;

namespace Assets.Code.Controllers
{
    public class CameraController : MonoBehaviour
    {
        public GameObjects.Camera camera;

        private Vector3 movment;
        private Vector3 rotation;

        void Update()
        {
            this.cameraTranslationListener();
            this.cameraRotationListener();
        }

        void OnGUI()
        {
            if (GUI.Button(new Rect(Screen.width - 390, Screen.height - 50, 120, 30), "Align on X axis"))
            {
                Vector3 actualRotatioin = this.camera.GetEulerAngles();
                this.camera.SetRotation(new Vector3(0, actualRotatioin.y, actualRotatioin.z));
            }

            if (GUI.Button(new Rect(Screen.width - 260, Screen.height - 50, 120, 30), "Align on Y axis"))
            {
                Vector3 actualRotatioin = this.camera.GetEulerAngles();
                this.camera.SetRotation(new Vector3(actualRotatioin.x, 0, actualRotatioin.z));
            }

            if (GUI.Button(new Rect(Screen.width - 130, Screen.height - 50, 120, 30), "Align on Z axis"))
            {
                Vector3 actualRotatioin = this.camera.GetEulerAngles();
                this.camera.SetRotation(new Vector3(actualRotatioin.x, actualRotatioin.y, 0));
            }

        }

        public Vector3 GetPosition()
        {
            return this.camera.GetPosition();
        }

        public Vector3 GetRotation()
        {
            return this.camera.GetEulerAngles();
        }

        public void SetPosition(Vector3 position)
        {
            this.camera.SetPosition(position);
        }

        public void SetRotation(Vector3 rotation)
        {
            this.camera.SetRotation(rotation);
        }

        protected void cameraTranslationListener()
        {
            if (Input.GetKey(KeyCode.A))
            {
                this.movment.x += -1;
            }
            if (Input.GetKey(KeyCode.D))
            {
                this.movment.x += 1;
            }
            if (Input.GetKey(KeyCode.Space))
            {
                if (Input.GetKey(KeyCode.W))
                {
                    this.movment.y += 1;
                }
                if (Input.GetKey(KeyCode.S))
                {
                    this.movment.y += -1;
                }
            }
            else
            {
                if (Input.GetKey(KeyCode.W))
                {
                    this.movment.z += 1;
                }
                if (Input.GetKey(KeyCode.S))
                {
                    this.movment.z += -1;
                }
            }

            this.camera.Translate(this.movment);
            this.movment = Vector3.zero;
        }

        protected void cameraRotationListener()
        {
            if (Input.GetKey(KeyCode.UpArrow))
            {
                this.rotation.x += 1;
            }
            if (Input.GetKey(KeyCode.DownArrow))
            {
                this.rotation.x += -1;
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
                    this.rotation.y += 1;
                }
                if (Input.GetKey(KeyCode.LeftArrow))
                {
                    this.rotation.y += -1;
                }
            }

            this.camera.Rotate(this.rotation);
            this.rotation = Vector3.zero;
        }
    }
}