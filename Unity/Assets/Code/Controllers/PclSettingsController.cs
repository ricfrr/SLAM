using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Assets.Code.Controllers
{
    public class PclSettingsController : MonoBehaviour {

        private string actualParam = null;
        private int actualAlgorithm = 0;
	    // Use this for initialization
	    void Start () {
		
	    }

        // Update is called once per frame
        void Update()
        {

            if (Input.GetKeyDown(KeyCode.Alpha0))
            {
                this.actualParam = "RESET";
            }

            if (Input.GetKeyDown(KeyCode.Alpha1))
            {
                this.actualAlgorithm++;
                int n = actualAlgorithm % 2;
                this.actualParam = "ALGORITHM\n" + n;
            }

            if (Input.GetKeyDown(KeyCode.Alpha2))
            {
                this.actualParam = "ITERATION\n"; // 1-20
            }

            if (Input.GetKeyDown(KeyCode.Alpha3))
            {
                this.actualParam = "CORRESPONDENCE\n"; // 1-200
            }

            if (Input.GetKeyDown(KeyCode.Alpha4))
            {
                this.actualParam = "EUCLIDEAN_FITNESS\n"; // 1-14
            }

            if (Input.GetKeyDown(KeyCode.Alpha5))
            {
                this.actualParam = "TRANSFORMATION_EPSILON\n"; // 1-14
            }

            if (Input.GetKeyDown(KeyCode.Alpha6))
            {
                this.actualParam = "NOISE"; // on off
            }

        }

        public bool isParamToSend()
        {
            return this.actualParam != null;
        }

        public string GetActualParam()
        {
            string tmp = this.actualParam;
            this.actualParam = null;
            return tmp;
        }
    }
}
