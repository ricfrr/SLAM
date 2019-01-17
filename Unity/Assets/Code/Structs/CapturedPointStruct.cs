using UnityEngine;

namespace Assets.Code.Structs
{
    [System.Serializable]
    public struct CapturedPointStruct
    {
        public Vector3[] points;
        public string filename;
        public Vector4[] colors;

        public CapturedPointStruct(Vector3[] points, string filename, Vector4[] colors)
        {
            this.points = points;
            this.filename = filename;
            this.colors = colors;
        }
    }
}