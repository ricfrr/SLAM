using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

namespace Assets.Code
{
    public class B : MonoBehaviour {

        private bool isCalled;

	    // Use this for initialization
	    void Start () {
            this.isCalled = false;	
	    }
	
	    // Update is called once per frame
	    void Update () {

            if (this.isCalled)
            {
                
            }
	    }

        public void OnGUI()
        {
            GUI.Label(new Rect(10, 40, 100, 100),  Time.frameCount.ToString());

        }

        public void Alma()
        {
            //this.isCalled = true;

            new Thread(() => {
                new WaitForSeconds(5);
                Debug.Log("B");
                this.isCalled = false;
            }).Start();
        }
    }
}
