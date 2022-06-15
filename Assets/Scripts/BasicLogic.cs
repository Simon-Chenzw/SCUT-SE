using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicLogic : MonoBehaviour
{
    public HealthBar healthBar;

    [Header("Settings")]
    public int BaseHP;
    public float BaseATK;
    public float BaseDEF;

    [Header("Status")]
    public int MaxHP;
    public int HP;
    public float ATK;
    public float DEF;

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
                OnDie();
            }
        }
    }

    public virtual void OnDie() { }

    public void SetMaxHP(int maxhp)
    {
        MaxHP = maxhp;
        HP = maxhp;
        healthBar.SetMaxHealth(MaxHP);
    }
}
