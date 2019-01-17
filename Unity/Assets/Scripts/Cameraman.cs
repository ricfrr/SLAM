using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class Cameraman : MonoBehaviour {

    public Camera main;
    public Camera cockpit;
    public GameObject car;

    public Light initiallight;
    public Light scanner;

    private bool driving = false;
    private Vector3 initialpose;
    private Vector3 initialrot;
    private Quaternion originalRotation;
    private float incockpitROM = 0.8f;

    public bool inside = false;

    // Use this for initialization
    void Start () {
        initialpose = cockpit.transform.position;
        originalRotation = cockpit.transform.rotation;
		
	}
	
	// Update is called once per frame
	void Update () {

        Vector3 v = car.transform.position;
        Vector3 c = main.transform.position;
        Vector3 r = v - c;
        Vector2 r2 = new Vector2(r.x, r.z);

        if(r2.magnitude <= 11f){
            inside = true;
        }

        if (inside){
            scanner.enabled = true;
            initiallight.enabled = false;
            main.enabled = false;
            cockpit.enabled = true;
        }
        else{
            scanner.enabled = false;
            initiallight.enabled = true;
            main.enabled = false;
            cockpit.enabled = false;
            main.enabled = true;
        }
	}

    void FixedUpdate()
    {
        if(!driving){
            MoveInCockpit();
        }
        else{
            DriveCar();
        }

    }

    public void setDriving(bool enabled){
        if(!driving){
            cockpit.transform.rotation = originalRotation;
            cockpit.transform.position = initialpose;
            Vector3 translation = new Vector3(0.0f, 0.0f, incockpitROM / 3);
            cockpit.transform.Translate(translation);
        }

        driving = enabled;
    }

    void MoveInCockpit(){
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        Vector3 rotation = new Vector3(0.0f, moveHorizontal, 0.0f);
        cockpit.transform.Rotate(rotation);

        Vector3 translation = new Vector3(0.0f, 0.0f, moveVertical/10);

        if(moveVertical > 0 && cockpit.transform.position.z < initialpose.z + incockpitROM){
            cockpit.transform.rotation = originalRotation;
            cockpit.transform.Translate(translation);
        }
        else if (moveVertical < 0 && cockpit.transform.position.z > initialpose.z - incockpitROM){
            cockpit.transform.rotation = originalRotation;
            cockpit.transform.Translate(translation);
        }
        else if(
                cockpit.transform.rotation.y < originalRotation.z + incockpitROM &&
                cockpit.transform.rotation.y > originalRotation.z - incockpitROM
               ){
            rotation.y = 0f;
            rotation.x = moveVertical/5;
            cockpit.transform.Rotate(rotation);
        }
    }

    void DriveCar(){
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        Vector3 rot = new Vector3(0f, moveHorizontal, 0f);
        Vector3 movement = new Vector3(0f, 0f, moveVertical/2);
        car.transform.Translate(movement);
        if(moveVertical != 0){
            car.transform.Rotate(rot);
        }
    }

}
