using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicLogic : MonoBehaviour
{
    [Header("Settings")]
    public int maxHP = 100;

    [Header("Status")]
    public int HP;

    void Start()
    {
        HP = maxHP;
    }
}
