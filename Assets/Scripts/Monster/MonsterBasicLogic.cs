using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterBasicLogic : BasicLogic
{
    [Header("Settings")]
    public int MonsterHP;
    public float MonsterATK;
    public float MonsterDEF;

    void Start()
    {
        SetMaxHP(MonsterHP);
        ATK = MonsterATK;
        DEF = MonsterDEF;
    }
}
