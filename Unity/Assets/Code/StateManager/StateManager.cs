using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Assets.Code.Interfaces;
using Assets.Code.States;

public class StateManager: MonoBehaviour {

    private IBaseState activeState;

	// Use this for initialization
	private void Start ()
    {
        this.activeState = new StartScreen(this);
    }
	
	// Update is called once per frame
	private void Update ()
    {
        if (this.activeState != null)
        {
            this.activeState.StateUpdate();
        }
	}

    private void OnGUI()
    {
        GUI.Box(new Rect(10, 40, 125, 40),
            "total frames: " + Time.frameCount.ToString() +
            "\nlast frame fps: " +((int)(1.0f / Time.smoothDeltaTime)).ToString());

        if (this.activeState != null)
        {
            this.activeState.StateGUI();
        }
    }

    public void SwitchState(IBaseState newState)
    {
        this.activeState = newState;
    }
}
