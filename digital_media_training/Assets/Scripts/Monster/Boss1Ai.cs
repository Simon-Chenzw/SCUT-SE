using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss1Ai : MonoBehaviour
{
    public Vector3[] Position;
    private int CurrentPostion;

    void Start()
    {
        transform.position = Position[1];
        CurrentPostion = 1;
    }

    void Teleport()
    {
        if (CurrentPostion == 0)
        {
            transform.position = Position[1];
            CurrentPostion = 1;
        }
        else if (CurrentPostion == Position.Length - 1)
        {
            transform.position = Position[Position.Length - 2];
            CurrentPostion = Position.Length - 2;
        }
        else if (Random.value <= 0.5)
        {
            transform.position = Position[CurrentPostion - 1];
            CurrentPostion = CurrentPostion - 1;
        }
        else
        {
            transform.position = Position[CurrentPostion + 1];
            CurrentPostion = CurrentPostion + 1;
        }
    }

    [System.Serializable]
    public struct SkillPair
    {
        public float limit;
        public MonsterSkill skill;
    }

    public SkillPair[] Skills;

    void Attack()
    {
        int cnt = 0;
        MonsterSkill skill = null;
        foreach (var pr in Skills)
        {
            if (logic.HP / logic.MaxHP <= pr.limit)
            {
                cnt += 1;
                if (Random.value < 1.0 / cnt)
                {
                    skill = pr.skill;
                }
            }
        }
        Debug.Log($"use skill {skill.SkillName}");
        if (skill != null)
            logic.UseSkill(skill);
    }

    public float TeleportTime;
    private float PrevTeleport;
    public float AttackTime;
    private float PrevAttack;

    void Update()
    {
        if ((PrevTeleport + TeleportTime) <= Time.time)
        {
            Teleport();
            PrevTeleport = Time.time;
        }
        if ((PrevAttack + AttackTime) <= Time.time)
        {
            Attack();
            PrevAttack = Time.time;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // getter

    MonsterBasicLogic logic
    {
        get { return gameObject.GetComponent<MonsterBasicLogic>(); }
    }
}
