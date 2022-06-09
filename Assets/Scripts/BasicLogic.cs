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
        ATK = 50.0f;
        DEF = 20.0f;
    }

    public virtual void TakeDamage(float damage)
    {
        int RealDamage = Mathf.CeilToInt(damage / (DEF / 100 + 1));
        Debug.Log(gameObject.ToString() + " get damage " + RealDamage.ToString());
        if (RealDamage > 0)
        {
            HP -= RealDamage;
            healthBar.SetHealth(HP);
            if (HP <= 0)
            {
                Destroy(gameObject);
            }
        }
    }
}
