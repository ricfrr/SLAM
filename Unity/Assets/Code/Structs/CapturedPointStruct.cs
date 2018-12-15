using UnityEngine;

namespace Assets.Code.Structs
{
    [System.Serializable]
    public struct CapturedPointStruct
    {
        public Vector3[] points;
        public string filename;

        public CapturedPointStruct(Vector3[] points, string filename)
        {
            this.points = points;
            this.filename = filename;
        }
    }
}