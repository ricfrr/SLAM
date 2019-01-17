using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

using UnityEngine.SceneManagement;

public class PlayerScript : MonoBehaviour {

    public Camera mainCamera;
    public Camera faceCamera;
    public Camera blackout;
    public GameObject man;
    public float speed;

    private Rigidbody rb;
    private float t = 0.2f;
    private int jump = 0;

    private bool fall = false;
    private bool fell = false;

    // Use this for initialization
    void Start () {
        print("started the game");
        faceCamera.enabled = false;
        mainCamera.enabled = true;
        blackout.enabled = false;
        rb = GetComponent<Rigidbody>();
    }
	
	// Update is called once per frame
	void Update () {

        float distance_z = mainCamera.transform.position.z - faceCamera.transform.position.z;
        float distance_y = mainCamera.transform.position.y - faceCamera.transform.position.y;
       // Debug.Log("distance between the cameras is: " + distance_z + " and " + distance_y);

        if (distance_z > 1 && !fall)
        {
            if (Math.Abs(distance_y) < 3){
                distance_y = 0;
                Vector3 vector_r = new Vector3(mainCamera.transform.rotation.z, 0f, 0f);
                mainCamera.transform.Rotate(vector_r);
            }
            //Debug.Log("main camera rotation = " + mainCamera.transform.rotation.x + " " + mainCamera.transform.rotation.y + " " + mainCamera.transform.rotation.z);

                Vector3 vector = new Vector3(0f, distance_y / 100f, 0.05f+distance_z / 1000f);
            mainCamera.transform.Translate(vector);
        }
        else if(!fall)
        {
            mainCamera.enabled = false;
            faceCamera.enabled = true;

            Vector3 movement = new Vector3(0.0f, 0.0f, t);
            //Debug.Log("man's current pos " + man.transform.position.z);

            if(jump%50 == 0){
                movement.y = 0.25f;
            }

            man.transform.Translate(movement);
            jump += 1;

            if(man.transform.position.y < 99){
                movement.z = 5.0f;
                man.transform.Translate(movement);
                fall = true;
            }
        }
        else if (fall){
            if (!fell)
            {
                Vector3 rotation = new Vector3(-90.0f, 0.0f, 0.0f);
                man.transform.Rotate(rotation);
                fell = true;
                Debug.Log("fell!!");
                Debug.Log("begin timer");
                StartCoroutine(Begin());
            }
        }
		
	}

    IEnumerator Begin()
    {
        Debug.Log("wait 8 seconds");
        yield return new WaitForSeconds(8);
        blackout.enabled = true;
        faceCamera.enabled = false;
        Debug.Log("waiting over");
        StartCoroutine(Next());
    }

    IEnumerator Next()
    {
        yield return new WaitForSeconds(2);

        SwitchScene();
    }

    void SwitchScene()
    {
        Debug.Log("should switch scene");
        SceneManager.LoadScene(sceneName: "IntroScene");

    }
}
