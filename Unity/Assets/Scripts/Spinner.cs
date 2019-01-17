using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Spinner : MonoBehaviour {

    public Light laser;

    public float velocity = 5;
    public float angle = 10;
    public GameObject veloSlider;

    public bool spin = false;

	// Use this for initialization
	void Start () {
        velocity = GameObject.Find("ScannerVelocitySlider").GetComponent<Slider>().value;
        angle = 10;
 
 
	}

        
    // Update is called once per frame
    void Update() { 
        if(laser.enabled){
            spin = true;
        }
        if(spin){
            Spin();
        }
    }


    void Spin(){
            laser.spotAngle = angle;
            Vector3 vector = new Vector3(0f, 1f * velocity, 0f);
            laser.transform.Rotate(vector);
        }


    public void SliderChanged(Slider slider){
        velocity = slider.value;
    }

    public void Sliding(float slider){
        velocity = slider;

    }
        
    public void SlidingSize(float slider){
        angle = slider;

    }
}
