using UnityEngine;
using Assets.Code.Interfaces;

namespace Assets.Code.States
{
    public class StartScreen : IBaseState
    {
        private StateManager manager;

        public StartScreen(StateManager manager)
        {
            this.manager = manager;
        }

        public void StateUpdate()
        {
            
        }

        public void StateGUI()
        {
            GUI.Label(new Rect(10, 10, 100, 20), "Start Screen");

            if (GUI.Button(new Rect(10, Screen.height-50, 100, 30), "Walk in pit"))
            {
                this.manager.SwitchState(new WalkInPitState(this.manager));
            }

            if (GUI.Button(new Rect(130, Screen.height - 50, 100, 30), "Load Result"))
            {
                this.manager.SwitchState(new LoadResultState(this.manager));
            }

        }
    }
}