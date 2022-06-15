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
}
