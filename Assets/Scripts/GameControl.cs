using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameControl : MonoBehaviour
{
    void Update()
    {
        if (Input.GetKeyUp(GlobalSetting.ExitKey))
        {
            Application.Quit();
        }
    }
}
