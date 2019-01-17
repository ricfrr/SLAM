using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class firstperson : MonoBehaviour {

    public Vector3 endposition;
    public Camera cam;

    private float w = 0f;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
    }

    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");


        float walking = Math.Abs(moveVertical);


        if (walking >= 1 || Math.Abs(moveHorizontal) >= 1)
        {
            w = w+0.1f;
            float result = (float)Math.Sin(w*1.2f);
            Vector3 rot = new Vector3(0f, moveHorizontal, 0f);
            Vector3 movement = new Vector3(0f, result / 7, moveVertical / 5);
            cam.transform.Translate(movement);
            cam.transform.Rotate(rot);
        }

    }

}
