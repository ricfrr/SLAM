using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Assets.Code.GameObjects
{
    public class Extrema : MonoBehaviour {

        private Vector3[] pointsToReach;
        private Mesh extremaMesh;
        private Material extremaMaterial;

        private bool isInitaliesed;
        private bool isExtemaActive;

        // Use this for initialization
        void Start ()
        {
            this.extremaMesh = new Mesh();
            this.isInitaliesed = false;
            this.isExtemaActive = false;
        }
	
	    // Update is called once per frame
	    void Update () {

            if (this.isExtemaActive)
            {
                this.DrawExtrema();
            }
        }

        public void ExtremaListener()
        {
            this.isExtemaActive = !this.isExtemaActive;

            if (!this.isExtemaActive)
            {
                this.ClearExtrema();
            }
        }

        public void Init(Vector3[] pointsToReach, Material extremaMaterial)
        {
            this.pointsToReach = pointsToReach;
            this.extremaMaterial = extremaMaterial;

            this.isInitaliesed = true;
            Debug.Log("Extrema init");
        }

        private void DrawExtrema()
        {

            int max = 30000;
            Vector3[] vertices = new Vector3[max];
            int[] indices = new int[max];
            for (int i = 0; i < max; i++)
            {
                int e = Random.Range(0, this.pointsToReach.Length);
                vertices[i] = transform.InverseTransformPoint(this.pointsToReach[e]);
                indices[i] = i;
            }

            this.extremaMesh.vertices = vertices;
            this.extremaMesh.SetIndices(indices, MeshTopology.Points, 0);

            this.extremaMesh.RecalculateBounds();

            this.gameObject.GetComponent<MeshFilter>().mesh = this.extremaMesh;
            this.gameObject.GetComponent<MeshRenderer>().material = this.extremaMaterial;
        }

        private void ClearExtrema()
        {
            this.extremaMesh.Clear();
        }
    }
}

