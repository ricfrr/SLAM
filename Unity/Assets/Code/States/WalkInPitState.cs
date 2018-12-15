using UnityEngine;
using Assets.Code.Interfaces;
using Assets.Code.Controllers;

namespace Assets.Code.States
{
    public class WalkInPitState : IBaseState
    {
        private StateManager manager;

        private GameObject walkInPitGameObject;

        private bool is3DcameraActive;
        private string activateCameraButtonText;

        public WalkInPitState(StateManager manager)
        {
            this.manager = manager;

            // load into the scene
            this.walkInPitGameObject = Object.Instantiate(Resources.Load("Walk In Pit", typeof(GameObject))) as GameObject;
        }

        public void StateUpdate()
        {

        }

        public void StateGUI()
        {
            GUI.Label(new Rect(10, 10, 100, 20), "Walk In Pit");

            if (GUI.Button(new Rect(10, Screen.height - 50, 100, 30), "Back"))
            {
                this.changeState(new StartScreen(this.manager));
            }
        }

        private void changeState(IBaseState newState)
        {
            Object.Destroy(this.walkInPitGameObject);
            this.manager.SwitchState(newState);
        }
    }
}
