using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CharacterBasicLogic : BasicLogic
{
    [Header("Settings")]
    public SkillItem[] Skills;

    [Header("Status")]
    private int gold = 0;

    // Note: Public for testing
    public List<BuffItem> Buffs = new List<BuffItem>();

    void Start()
    {
        SetStatus();
        GetGold(0);
    }

    void Update()
    {
        if (Input.GetKeyDown(GlobalSetting.CommonAttackKey))
        {
            UseSkill(Skills[0].Skill);
        }
        else if (Input.GetKeyDown(GlobalSetting.CommonManaAttackKey))
        {
            UseSkill(Skills[1].Skill);
        }
    }

    public override void TakeDamage(float damage)
    {
        damage *= 1 + Vulnerable;
        base.TakeDamage(damage);
    }

    public void GetGold(int got)
    {
        gold += got;
        GameObject.Find("GoldText").GetComponent<Text>().text = $"Gold: \t {gold}";
    }

    public override void OnDie()
    {
        Destroy(gameObject);
    }

    void SetStatus()
    {
        int hp_add = 0;
        float hp_mul = 0.0f;
        float atk_add = 0.0f;
        float atk_mul = 0.0f;
        float def_add = 0.0f;
        float def_mul = 0.0f;

        foreach (Item item in Buffs)
        {
            hp_add += item.HpAdd;
            hp_mul += item.HpMul;
            atk_add += item.AtkAdd;
            atk_mul += item.AtkMul;
            def_add += item.DefAdd;
            def_mul += item.DefMul;
        }

        SetMaxHP(Mathf.CeilToInt((BaseHP + hp_add) * (1 + hp_mul)));
        ATK = (BaseATK + atk_add) * (1 + atk_mul);
        DEF = (BaseDEF + def_add) * (1 + def_mul);
    }

    float Vulnerable
    {
        get
        {
            float Vulnerable = 0.0f;
            foreach (Item item in Buffs)
            {
                Vulnerable += item.Vulnerable;
            }
            return Vulnerable;
        }
    }
}
