using UnityEngine;
using System.Collections;
using System.Threading;
using System.IO;
using System;
using System.Collections.Generic;
using UnityEditor;

public class Inporter : MonoBehaviour
{
    public GameObject loadedObject;
    private string incomeStream;
    private Vector3[] loadedPoints;

    private bool readyToPlot = false;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (this.readyToPlot)
        {
            this.Ploting();
            this.readyToPlot = false;
        }
    }

    public void SetPoints(string input)
    {
        this.incomeStream = input;
        this.readyToPlot = true;
    }

    private void Ploting()
    {
        string[] points_xyz = incomeStream.Split('\n');

        int nPoints = Convert.ToInt32(points_xyz.Length);
        this.loadedPoints = new Vector3[nPoints];
        int[] indices = new int[nPoints];

        int i = 0;
        foreach (string point in points_xyz)
        {
            indices[i] = i;

            string[] vector = point.Split();
            this.loadedPoints[i] = new Vector3(
                Convert.ToSingle(vector[0]),
                Convert.ToSingle(vector[1]),
                Convert.ToSingle(vector[2])
            );
            i++;
        }

        // ------------------------------------------------
                
                
        Mesh pointMesh = new Mesh();
        pointMesh.vertices = this.loadedPoints;
        pointMesh.SetIndices(indices, MeshTopology.Points, 0);
        pointMesh.RecalculateBounds();
        this.loadedObject.GetComponent<MeshFilter>().mesh = pointMesh;

        Material material = new Material(Resources.Load<Shader>("GeometryShader"));
        material.SetFloat("_Size", 1);
        material.SetColor("_Color", Color.cyan);
        this.loadedObject.GetComponent<MeshRenderer>().material = material;

    }
}
