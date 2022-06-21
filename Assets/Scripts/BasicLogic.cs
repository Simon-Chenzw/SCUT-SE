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
    public BoxCollider2D BodyBox;

    [Header("Status")]
    public int MaxHP;
    public int HP;
    public float ATK;
    public float DEF;
    private float GlobalCD = 0.0f;
    private Dictionary<Skill, float> CD = new Dictionary<Skill, float>();

    public virtual void TakeDamage(float damage)
    {
        int RealDamage = Mathf.CeilToInt(damage / (DEF / 100 + 1));
        Debug.Log(gameObject.ToString() + " get damage " + RealDamage.ToString());
        if (RealDamage > 0)
        {
            HP -= RealDamage;
            healthBar?.SetHealth(HP);
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
        healthBar?.SetMaxHealth(MaxHP);
    }

    public void SetATK(float atk)
    {
        ATK = atk;
    }

    public void SetDEF(float def)
    {
        DEF = def;
    }

    public bool InGlobalCD()
    {
        return Time.time < GlobalCD;
    }

    public bool UseSkill(Skill skill)
    {
        // CD check
        if (!CD.ContainsKey(skill))
            CD[skill] = 0.0f;
        if (Time.time < GlobalCD)
            return false;
        if (Time.time < CD[skill])
            return false;

        skill.CreateSkill(BodyBox.bounds, transform);

        GlobalCD = Time.time + skill.GlobalCD;
        CD[skill] = Time.time + skill.CD;
        return true;
    }
}
