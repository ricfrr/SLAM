using UnityEngine;
using System.Collections;
using System.Threading;
using System.IO;
using System;
using System.Collections.Generic;
using UnityEditor;
using System.Globalization;

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
        }
    }

    public void SetPoints(string input)
    {
        if(!this.readyToPlot)
        {
            this.incomeStream = input;
            this.readyToPlot = true;
        }
    }

    private void Ploting()
    {
        //Debug.Log(incomeStream);
        string[] points_xyz = incomeStream.Split('\n');
        points_xyz[points_xyz.Length-1] = "0.0000 0.0000 0.0000";
        int nPoints = points_xyz.Length;
        this.loadedPoints = new Vector3[nPoints];
        int[] indices = new int[nPoints];

        int i = 0;
        CultureInfo cinfo = new CultureInfo("en-US");
        foreach (string point in points_xyz)
        {
            indices[i] = i;

            string[] vector = point.Split(' ');

            this.loadedPoints[i] = new Vector3(
                Convert.ToSingle(vector[0].Substring(0, 5), cinfo),
                Convert.ToSingle(vector[1].Substring(0, 5), cinfo),
                Convert.ToSingle(vector[2].Substring(0, 5), cinfo)
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

        this.readyToPlot = false;
    }
}
