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
    private Vector3[] loadedPoints;

    // Use this for initialization
    void Start()
    {
        ImportFromFile();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void ImportFromFile()
    {
        //new Thread(() =>
        //{
        string path = EditorUtility.OpenFilePanel("Load pcd", "", "pcd");
        try
            {
                StreamReader reader = new StreamReader(path, false);

                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();
                reader.ReadLine();

                int nPoints = Convert.ToInt32(reader.ReadLine().Split()[1]);
                this.loadedPoints = new Vector3[nPoints];
                int[] indices = new int[nPoints];

                reader.ReadLine();

                string line;
                int i = 0;
                while ((line = reader.ReadLine()) != null)
                {
                    indices[i] = i;

                    string[] vector = line.Split();
                    this.loadedPoints[i] = new Vector3(
                        Convert.ToSingle(vector[0]),
                        Convert.ToSingle(vector[1]),
                        Convert.ToSingle(vector[2])
                    );
                    i++;
                }

                Debug.Log(i);

                reader.Close();

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
            catch (Exception ex)
            {
                Debug.Log("The file could not be read:");
                Debug.Log(ex.Message);
            }

        //}).Start();
    }
}
