using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RadioScript : MonoBehaviour {

    public GameObject song1;
    public GameObject song2;
    public GameObject song3;

    public bool song_1_active = false;
    public bool song_2_active = false;
    public bool song_3_active = false;

    private AudioSource song1_source;
    private AudioSource song2_source;
    private AudioSource song3_source;

    // Use this for initialization
    void Start () {
        song1_source = song1.GetComponent<AudioSource>();
        song2_source = song2.GetComponent<AudioSource>();
        song3_source = song3.GetComponent<AudioSource>();
    }
	
	// Update is called once per frame
	void Update () {

        if (song_1_active)
        {
            if (!song1_source.isPlaying)
            {
                song1_source.Play();
            }
            song2_source.Stop();
            song3_source.Stop();
        }
        else if (song_2_active)
        {
            if (!song2_source.isPlaying)
            {
                song2_source.Play();
            }
            song1_source.Stop();
            song3_source.Stop();
        }

        else if (song_3_active)
        {
            if (!song3_source.isPlaying) {
                song3_source.Play();
            }


            song1_source.Stop();
            song2_source.Stop();
        }
        else
        {
            song1_source.Stop();
            song2_source.Stop();
            song3_source.Stop();
        }

    }
}
