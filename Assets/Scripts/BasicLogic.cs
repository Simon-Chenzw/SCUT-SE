using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicLogic : MonoBehaviour
{
    [Header("Settings")]
    public int maxHP = 100;
    public int maxMP = 100;

    [Header("Status")]
    public int HP;
    public int MP;
    public float ATK;
    public float DEF;

    void Start()
    {
        HP = maxHP;
        MP = maxMP;
    }
}
