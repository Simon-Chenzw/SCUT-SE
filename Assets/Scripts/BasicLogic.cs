using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicLogic : MonoBehaviour
{
    public HealthBar healthBar;

    [Header("Settings")]
    public int maxHP = 100;
    public int maxMP = 50;

    [Header("Status")]
    public int HP;
    public int MP;
    public float ATK;
    public float DEF;

    void Start()
    {
        HP = maxHP;
        MP = maxMP;
        healthBar.SetMaxHealth(maxHP);
    }

    protected void TakeDamage(int damage)
    {
        HP -= damage;
        healthBar.SetHealth(HP);
    }
}
