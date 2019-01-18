using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using Assets.Code.Structs;

namespace Assets.Code.GameObjects
{
    public class CapturedPoints : MonoBehaviour {

        public Camera camera;

        private List<Vector3[]> capturedPointsList;

        private Vector3[] pointsToReach;
        private float maxRange;
        private Material capturePointsMaterial;
        private Vector4[] colors;

        public void Init(Vector3[] pointsToReach, float maxRange, Material capturePointsMaterial)
        {
            this.pointsToReach = pointsToReach;
            this.maxRange = maxRange;
            this.capturePointsMaterial = capturePointsMaterial;
            colors = new Vector4[this.pointsToReach.Length];
            Debug.Log("CapturedPoints init");
        }

        public void CapturePoints(LinkedList<CapturedPointStruct> capturedPointList)
        {
            this.DrawLastCapturedPoints(this.CalcPointCloud(), capturedPointList);
        }

        private Vector3[] CalcPointCloud()
        {
            Vector3[] pts = new Vector3[this.pointsToReach.Length];

            Vector3 worldTarget;
            Ray ray;
            RaycastHit hit;
            Transform cameraTransform = this.camera.transform;

            for (int i = 0; i < this.pointsToReach.Length; i++)
            {
                worldTarget = cameraTransform.TransformPoint(this.pointsToReach[i]);
                ray = new Ray(cameraTransform.position, worldTarget - cameraTransform.position);
                if (Physics.Raycast(ray, out hit))
                {
                    pts[i] = cameraTransform.InverseTransformPoint(hit.point);
                    Renderer rend = hit.transform.GetComponent<Renderer>();
                    MeshCollider meshCollider = hit.collider as MeshCollider;
                    Texture2D tex = rend.material.mainTexture as Texture2D;
                    Vector2 pixelUV = hit.textureCoord;
                    pixelUV.x *= tex.width;
                    pixelUV.y *= tex.height;
                    Color col = tex.GetPixel((int) pixelUV.x, (int) pixelUV.y);
                    colors[i] = col;
                    if(colors[i].x < 0.1 && colors[i].y < 0.1 && colors[i].z < 0.1)
                    {
                        pts[i] = new Vector3(0, 0, 0);
                        colors[i] = Color.black;
                    }
                    if (pts[i].magnitude > this.maxRange)
                    {
                        pts[i] = new Vector3(0, 0, 0);
                        colors[i] = Color.black;
                    }
                }
                else
                {
                    pts[i] = Vector3.zero;
                    colors[i] = Color.black;
                }
            }
            return pts;
        }

        private void DrawLastCapturedPoints(Vector3[] points, LinkedList<CapturedPointStruct> capturedPointList)
        {
            Transform cameraTransform = this.camera.transform;
            string filename = cameraTransform.position.ToString() + cameraTransform.eulerAngles.ToString();

            GameObject capturedPoints = new GameObject();
            this.makeCapturedPoints(ref capturedPoints, ref cameraTransform);

            Mesh pointMesh = new Mesh();

            int max = 10000;
            Vector3[] vertices = new Vector3[max];
            int[] indices = new int[max];
            for (int i = 0; i < max; i++)
            {
                int e = Random.Range(0, points.Length);
                vertices[i] = cameraTransform.InverseTransformPoint(points[e]);
                indices[i] = i;
            }

            pointMesh.vertices = vertices;
            pointMesh.SetIndices(indices, MeshTopology.Points, 0);
            pointMesh.RecalculateBounds();

            capturedPoints.GetComponent<MeshFilter>().mesh = pointMesh;
            capturedPoints.GetComponent<MeshRenderer>().material = this.capturePointsMaterial;

            capturedPointList.AddLast(new CapturedPointStruct(vertices, filename, colors));
        }

        private void makeCapturedPoints(ref GameObject capturedPoints, ref Transform cameraTransform)
        {
            capturedPoints.name = "Points" + cameraTransform.position.ToString() + cameraTransform.rotation.ToString();
            capturedPoints.transform.parent = this.transform;
            capturedPoints.transform.localPosition = cameraTransform.position;
            capturedPoints.transform.localRotation = cameraTransform.rotation;
            capturedPoints.AddComponent<MeshFilter>();
            MeshRenderer mr = capturedPoints.AddComponent<MeshRenderer>();
            mr.receiveShadows = false;
            mr.shadowCastingMode = UnityEngine.Rendering.ShadowCastingMode.Off;
        }
    }

}
