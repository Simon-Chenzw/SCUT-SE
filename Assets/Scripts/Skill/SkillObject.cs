using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class SkillObject : MonoBehaviour
{
    protected Collider2D SkillCollider;

    protected float damage;

    public float attack;

    public abstract void CalculateSkillDamage();
}
