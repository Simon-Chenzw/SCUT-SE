using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterBasicLogic : BasicLogic
{
    void Start()
    {
        backpack.SetBuff(this);
    }

    void Update()
    {
        if (Input.GetKeyDown(GlobalSetting.CommonAttackKey))
        {
            UseSkill(backpack.SkillOne);
        }
        else if (Input.GetKeyDown(GlobalSetting.CommonManaAttackKey))
        {
            UseSkill(backpack.SkillTwo);
        }
    }

    public override void TakeDamage(float damage)
    {
        base.TakeDamage(damage * (1 + Vulnerable));
    }

    public override void OnDie()
    {
        Destroy(gameObject);
        GameObject.Find("GlobalGameController").GetComponent<GlobalGameControl>().GameOver();
    }

    ////////////////////////////////////////////////////////////////////////////
    // getter

    Backpack backpack
    {
        get { return GameObject.Find("Backpack").GetComponent<Backpack>(); }
    }

    float Vulnerable
    {
        get { return backpack.Vulnerable; }
    }
}
