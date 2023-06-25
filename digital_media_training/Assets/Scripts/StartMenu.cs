using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartMenu : MonoBehaviour
{
    void Update()
    {
        if (Input.anyKeyDown)
        {
            GameObject.Find("GlobalGameController").GetComponent<GlobalGameControl>().OnNextLevel();
        }
    }
}
