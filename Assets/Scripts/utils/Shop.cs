using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

public class Shop : MonoBehaviour, IPointerClickHandler
{
    public void OnPointerClick(PointerEventData eventData)
    {
        GameObject go = eventData.pointerCurrentRaycast.gameObject;
        Debug.Log("Clicked: " + go.name);
        if (go.name == "Exit")
            SceneManager.LoadScene("Scenes/Level1", LoadSceneMode.Single);
    }

    ////////////////////////////////////////////////////////////////////////////
    // WorkFlow
}
