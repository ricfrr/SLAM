using UnityEngine;
using UnityEditor;

namespace Assets.Code.GameObjects
{
    public class Camera : MonoBehaviour
    {
        public void Translate(Vector3 movment, float speed = 1.0f)
        {
            this.transform.transform.Translate(movment * speed);
        }

        public void Rotate(Vector3 rotation, float speed = 0.25f)
        {
            this.transform.transform.Rotate(rotation * speed);
        }

        public void SetPosition(Vector3 newPosition)
        {
            this.transform.transform.position = newPosition;
        }

        public void SetRotation(Vector3 newRotation)
        {
            this.transform.transform.eulerAngles = newRotation;
        }

        public Vector3 GetPosition()
        {
            return this.transform.transform.position;
        }

        public Vector3 GetEulerAngles()
        {
            return this.transform.transform.eulerAngles;
        }
    }
}
