using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterBasicLogic : BasicLogic
{
    //used to test skill
    public Skill skill1;
    public Skill skill2;
    Bounds BodyBounds;
    Transform CharacterTransform;

    void Start()
    {
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
}
