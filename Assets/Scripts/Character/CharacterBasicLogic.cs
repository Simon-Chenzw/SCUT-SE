using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterBasicLogic : BasicLogic
{
    [Header("Settings")]
    public Skill skill1;
    public Skill skill2;

    private Bounds BodyBounds;
    private Transform CharacterTransform;

    List<Item> Items;

    void Start()
    {
        SetStatus();
        CharacterTransform = gameObject.transform;
    }

    void Update()
    {
        if (Input.GetKeyDown(GlobalSetting.CommonAttackKey))
        {
            UseSkill(skill1);
        }
        else if (Input.GetKeyDown(GlobalSetting.CommonManaAttackKey)) { }
    }

    private void UseSkill(Skill skill)
    {
        BodyBounds = transform.GetChild(0).GetChild(0).GetComponent<BoxCollider2D>().bounds;
        skill.CreateSkill(BodyBounds, CharacterTransform);
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
        SetMaxHP(Mathf.CeilToInt((BaseHP + hp_add) * (1 + hp_mul)));
        ATK = (BaseATK + atk_add) * (1 + atk_mul);
        DEF = (BaseDEF + def_add) * (1 + def_mul);
    }
}
