using UnityEngine;
using UnityEditor;
using Assets.Code.Controllers;
using System.Collections.Generic;
using Assets.Code.Structs;

namespace Assets.Code.GameObjects
{
    [System.Serializable]
    public struct SizeInt
    {
        public int rows, cols;

        public SizeInt(int r, int c)
        {
            rows = r;
            cols = c;
        }
    }

    [System.Serializable]
    public struct FoV
    {
        public float h, v;

        public FoV(float hFov, float vFov)
        {
            h = hFov;
            v = vFov;
        }
    }

    public class _3dCamera : MonoBehaviour
    {
        // inputs
        [Tooltip("Field of View (degree)")]     public FoV FOV;
        [Tooltip("Image resolution (pixel)")]   public SizeInt Size;
        [Tooltip("Sensor max distance (m)")]    public float MaxRange;
        [Tooltip("Only for drawing (rgba)")]    public Color ExtremaPointsColor, ActualPointsColor;
        [Tooltip("Only for drawing (m)")]       public float PointDrawingScale;
        [Tooltip("Seconds (s)")]                public float period;

        // features in game objects
        public Extrema extrema;
        public CapturedPoints capturedPoints;
        // camera controller
        public CameraController cameraController;

        // last captured point cloud
        private CapturedPointStruct ladstCapturedPoints;

        private bool isCaptureing;
        private float nextActionTime;

        private Vector3[] pointsToReach;
        private bool initialized = false;
        private Material materialExtrema, materialActual;
        private Shader geometryShader;

        void Start()
        {
            this.cameraController.SetPosition(new Vector3(0, 0, 0));
            this.cameraController.SetRotation(new Vector3(0, 0, 0));
            this.geometryShader = Resources.Load<Shader>("GeometryShader");

            this.Init();

            this.isCaptureing = false;
        }

        void Update()
        {
            if (!this.initialized)
            {
                this.Init();
            }

            if (this.isCaptureing)
            {
                if(this.WaitForTime(this.period))
                {
                    this.capturedPoints.CapturePoints(this.ladstCapturedPoints);
                }
            }
        }

        void OnGUI()
        {
            if (GUI.Button(new Rect(Screen.width - 390, Screen.height - 90, 120, 30), "Draw Extrema"))
            {
                this.extrema.ExtremaListener();
            }

            if (GUI.Button(new Rect(Screen.width - 260, Screen.height - 90, 120, 30), "Capture points"))
            {
                this.isCaptureing = !this.isCaptureing;

                if (!this.isCaptureing)
                {
                    this.nextActionTime = 0.0f;
                }
            }
        }

        private bool WaitForTime(float period)
        {
            if (this.nextActionTime == 0.0f || Time.time > this.nextActionTime)
            {
                this.nextActionTime = Time.time + period;
                return true;
            }

            return false;
        }

        public bool IsInitialized() { return this.initialized; }

        void OnValidate() { this.initialized = false; }

        void Init()
        {
            this.materialExtrema = new Material(geometryShader);
            this.materialExtrema.SetFloat("_Size", this.PointDrawingScale);
            this.materialExtrema.SetColor("_Color", this.ExtremaPointsColor);

            this.materialActual = new Material(geometryShader);
            this.materialActual.SetFloat("_Size", this.PointDrawingScale);
            this.materialActual.SetColor("_Color", this.ActualPointsColor);

            if (this.Size.rows <= 0) Debug.LogError("INVALID INPUT for camera vertical resolution. Actual value is " + this.Size.rows);
            if (this.Size.cols <= 0) Debug.LogError("INVALID INPUT for camera horizontal resolution. Actual value is " + this.Size.cols);

            if (this.MaxRange <= 0) Debug.LogError("INVALID INPUT for camera max visual distance. Actual value is " + this.MaxRange);

            if (this.FOV.v < 0) Debug.LogError("INVALID INPUT for camera vertical field of view. Actual value is " + this.FOV.v);
            if (this.FOV.h < 0) Debug.LogError("INVALID INPUT for camera horizontal field of view. Actual value is " + this.FOV.h);

            if (this.period <= 0)
            {
                this.period = 1.0f;
                Debug.Log("INVALID time");
            }
            // change camera
            UnityEngine.Camera.main.fieldOfView = this.FOV.v;

            // z si allontana dal sensore
            // x verso il basso
            // y verso sinistra
            float minX = 0.0f - this.FOV.v / 2.0f;
            float maxX = 0.0f + this.FOV.v / 2.0f;

            float minY = 0.0f - this.FOV.h / 2.0f;
            float maxY = 0.0f + this.FOV.h / 2.0f;

            float deltaX = (maxX - minX) / (float)this.Size.rows;
            float deltaY = (maxY - minY) / (float)this.Size.cols;

            this.pointsToReach = new Vector3[this.Size.cols * this.Size.rows];

            for (int r = 0; r < this.Size.cols; r++)
            {
                for (int c = 0; c < this.Size.rows; c++)
                {
                    Vector3 p = new Vector3(0, 0, this.MaxRange);
                    p = Quaternion.Euler(minX + deltaX * 0.5f + deltaX * c, minY + deltaY * 0.5f + deltaY * r, 0) * p;
                    this.pointsToReach[r * this.Size.rows + c] = p;
                }
            }

            this.initialized = true;
            Debug.Log("Camera parameters updated!");

            this.extrema.Init(this.pointsToReach, this.materialExtrema);
            this.capturedPoints.Init(this.pointsToReach, this.MaxRange, this.materialActual);
        }

        public Vector3[] GetLastCapturedPoints()
        {
            return this.ladstCapturedPoints.points;
        }

        public Vector4[] GetLastCapturedColors()
        {
            return this.ladstCapturedPoints.colors;
        }

        //public int GetCapturedPointSize()
        //{
        //    return this.capturedPointList.Count;
        //}
    }
}