using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterBasicLogic : BasicLogic
{
    [Header("Settings")]
    public int CharacterHP = 100;
    public int CharacterATK = 100;
    public int CharacterDEF = 100;

    //used to test skill
    public Skill skill1;
    public Skill skill2;
    Bounds BodyBounds;
    Transform CharacterTransform;
    List<Item> Items;

    void Start()
    {
        SetStatus();
        CharacterTransform = gameObject.transform;
    }

    void UseSkill(Skill skill)
    {
        BodyBounds = transform.GetChild(0).GetChild(0).GetComponent<BoxCollider2D>().bounds;
        skill.CreateSkill(BodyBounds, CharacterTransform);
    }

    void Update()
    {
        if (Input.GetKeyDown(GlobalSetting.CommonAttackKey))
        {
            UseSkill(skill1);
        }
        else if (Input.GetKeyDown(GlobalSetting.CommonManaAttackKey)) { }
    }

    void SetStatus()
    {
        int hp_add = 0;
        float hp_mul = 0.0f;
        float atk_add = 0.0f;
        float atk_mul = 0.0f;
        float def_add = 0.0f;
        float def_mul = 0.0f;
        if (Items != null)
        {
            foreach (Item item in Items)
            {
                hp_add += item.HpAdd;
                hp_mul += item.HpMul;
                atk_add += item.AtkAdd;
                atk_mul += item.AtkMul;
                def_add += item.DefAdd;
                def_mul += item.DefMul;
            }
        }
        SetMaxHP(Mathf.CeilToInt((CharacterHP + hp_add) * (1 + hp_mul)));
        ATK = (CharacterATK + atk_add) * (1 + atk_mul);
        DEF = (CharacterDEF + def_add) * (1 + def_mul);
    }
}
