using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class SkillBase : MonoBehaviour
{
    public string SkillName;
    public int CostMP;
    public float SkillCD;

    public float attack;
    public LayerMask MonsterLayerMask; //

    public LayerMask CharacterLayerMask; //

    public abstract void UseSkill();

    public abstract void SkillDamage();
}
