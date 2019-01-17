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

    private AudioSource last_played;

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
                last_played = song1_source;
            }
            song2_source.Stop();
            song3_source.Stop();
        }
        else if (song_2_active)
        {
            if (!song2_source.isPlaying)
            {
                song2_source.Play();
                last_played = song2_source;
            }
            song1_source.Stop();
            song3_source.Stop();
        }

        else if (song_3_active)
        {
            if (!song3_source.isPlaying) {
                song3_source.Play();
                last_played = song3_source;
            }


            song1_source.Stop();
            song2_source.Stop();
        }
        else
        {
            song1_source.Stop();
            song2_source.Stop();
            song3_source.Stop();
            //last_played = null;
        }

    }

  public void PlaySong1(){
        if (song_1_active)
        {
            song_1_active = false;
        }
        else{
            song_1_active = true;
            song_2_active = false;
            song_3_active = false;
        }

    }

    public void PlaySong2()
    {
        if (song_2_active)
        {
            song_2_active = false;
        }
        else
        {
            song_2_active = true;
            song_1_active = false;
            song_3_active = false;
        }

    }

    public void PlaySong3()
    {
        if (song_3_active)
        {
            song_3_active = false;
        }
        else
        {
            song_3_active = true;
            song_2_active = false;
            song_1_active = false;
        }

    }

    public void PlayNext(){

        if(song_1_active){
            PlaySong2();
        }
        else if (song_2_active){
            PlaySong3();
        }
        else if(song_3_active){
            PlaySong1();
        }
    }

    public void PlayPrevious()
    {

        if (song_1_active)
        {
            PlaySong3();
        }
        else if (song_2_active)
        {
            PlaySong1();
        }
        else if (song_3_active)
        {
            PlaySong2();
        }
    }

    public void PlaySong()
    {

        if (last_played == null)
        {
            PlaySong1();
        }
        else
        {

            if(last_played == song1_source){
                PlaySong1();
            }else if (last_played == song2_source){
                PlaySong2();
            }else if (last_played == song3_source){
                PlaySong3();
            }
            else{
                Debug.Log("nothing");
            }
        }
    }
    }
