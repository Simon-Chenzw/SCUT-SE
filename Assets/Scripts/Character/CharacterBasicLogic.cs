using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterBasicLogic : BasicLogic
{
    // NOTE: For testing
    void Start()
    {
        HP = maxHP;
        MP = maxMP;
        healthBar.SetMaxHealth(maxHP);
        ATK = 40;
        DEF = 0.5f;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.J))
        {
            TakeDamage(10);
        }
    }
}
