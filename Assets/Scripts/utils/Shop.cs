using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Shop : MonoBehaviour, IPointerClickHandler
{
    public void OnPointerClick(PointerEventData eventData)
    {
        GameObject go = eventData.pointerCurrentRaycast.gameObject;
        Debug.Log("Clicked: " + go.name);
        if (go.name == "Exit")
            GameObject.Find("GlobalGameController").GetComponent<GlobalGameControl>().OnShopOut();
    }

    ////////////////////////////////////////////////////////////////////////////
    // WorkFlow
}
