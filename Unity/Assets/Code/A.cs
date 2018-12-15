using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Assets.Code
{
    public class A : MonoBehaviour {

        public B b;
        // Use this for initialization
        void Start () {
	    }
	
	    // Update is called once per frame
	    void Update () {
        }

        void OnGUI()
        {
            GUI.Label(new Rect(10, 10, 100, 100),  Time.frameCount.ToString());

            if (GUI.Button(new Rect(Screen.width - 130, Screen.height - 50, 120, 30), "Align on Z axis"))
            {
                //GameObject.Find("Korte (B)").GetComponent(typeof (B)).Alma();
                this.b.Alma();
            }
        }
    }
}
