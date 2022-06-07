using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterBasicLogic : BasicLogic
{
    public void Start()
    {
        HP = maxHP;
        MP = maxMP;
        healthBar.SetMaxHealth(maxHP);
        ATK = 40;
        DEF = 1.0f;
    }

    public override void TakeDamage(float damage)
    {
        if (damage > 0)
        {
            Debug.Log(damage);
            HP -= (int)(damage * DEF);
            healthBar.SetHealth(HP);
            if (HP <= 0)
            {
                Destroy(gameObject);
            }
        }
    }
}
