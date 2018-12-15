using UnityEngine;
using UnityEditor;
using Assets.Code.Interfaces;

namespace Assets.Code.States
{
    public class LoadResultState : IBaseState
    {
        private StateManager manager;

        private GameObject loadResult;

        public LoadResultState(StateManager manager)
        {
            this.manager = manager;

            this.loadResult = Object.Instantiate(Resources.Load("Load Result", typeof(GameObject))) as GameObject;
        }

        public void StateUpdate()
        {

        }

        public void StateGUI()
        {
            GUI.Label(new Rect(10, 10, 100, 20), "Load Result");

            if (GUI.Button(new Rect(10, Screen.height - 50, 100, 30), "Back"))
            {
                this.changeState(new StartScreen(this.manager));
            }

        }

        private void changeState(IBaseState newState)
        {
            Object.Destroy(this.loadResult);
            this.manager.SwitchState(newState);
        }
    }
}