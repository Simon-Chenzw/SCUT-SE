using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterBasicLogic : BasicLogic
{
    [Header("Settings")]
    public int GrowHP;
    public float GrowATK;
    public float GrowDEF;

    void Start()
    {
        int CurrentWave = GameObject.Find("GameController").GetComponent<GameControl>().CurrentWave;
        SetMaxHP(BaseHP + GrowHP * CurrentWave);
        healthBar.SetMaxHealth(MaxHP);
        ATK = BaseATK + GrowATK * CurrentWave;
        DEF = BaseDEF + GrowDEF * CurrentWave;
    }

    public override void OnDie()
    {
        GameObject.Find("GameController").GetComponent<GameControl>().CurrentMonsterNumber--;
        Destroy(gameObject);
    }

    //Used to test Monster's attack

    void UseSkill(Skill skill)
    {
        Bounds BodyBounds = transform.GetChild(0).GetChild(0).GetComponent<BoxCollider2D>().bounds;
        skill.CreateSkill(BodyBounds, transform);
    }

    public Skill skill1;
    private KeyCode TestKey = KeyCode.U;

    void Update()
    {
        if (Input.GetKeyDown(TestKey))
        {
            UseSkill(skill1);
        }
    }
}
