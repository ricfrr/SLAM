using UnityEngine;

namespace Assets.Code.Structs
{
    [System.Serializable]
    public struct CapturedPointStruct
    {
        public Vector3[] points;
        public Vector4[] colors;

        public CapturedPointStruct(Vector3[] points, Vector4[] colors)
        {
            this.points = points;
            this.colors = colors;
        }
    }
}