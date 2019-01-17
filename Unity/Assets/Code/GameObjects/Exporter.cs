using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using Assets.Code.Structs;

namespace Assets.Code.GameObjects
{
    public class Exporter : MonoBehaviour
    {

        public void ExportToFile(LinkedList<CapturedPointStruct> capturedPoints)
        {
            foreach (CapturedPointStruct data in capturedPoints)
            {
                new Thread(() =>
                {
                    StreamWriter writer = new StreamWriter("exports/" + data.filename + ".pcd", false);

                    writer.WriteLine("# .PCD v.7 - Point Cloud Data file format");
                    writer.WriteLine("VERSION .7");
                    writer.WriteLine("FIELDS x y z");
                    writer.WriteLine("SIZE 4 4 4");
                    writer.WriteLine("TYPE F F F");
                    writer.WriteLine("COUNT 1 1 1");
                    writer.WriteLine("WIDTH " + data.points.Length.ToString());
                    writer.WriteLine("HEIGHT 1");
                    writer.WriteLine("VIEWPOINT 0 0 0 1 0 0 0");
                    writer.WriteLine("POINTS " + data.points.Length.ToString());
                    writer.WriteLine("DATA ascii");

                    for (int i = 0; i < data.points.Length; i++)
                    {
                        writer.Write(data.points[i].x.ToString("0.0000"));
                        writer.Write(" ");
                        writer.Write(data.points[i].y.ToString("0.0000"));
                        writer.Write(" ");
                        writer.WriteLine(data.points[i].z.ToString("0.0000"));
                    }

                    writer.Close();

                }).Start();
            }
        }
    }
}
