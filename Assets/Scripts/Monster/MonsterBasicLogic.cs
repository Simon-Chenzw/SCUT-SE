using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterBasicLogic : BasicLogic
{
    [Header("Settings")]
    public int GrowHP;
    public float GrowATK;
    public float GrowDEF;
    public int GoldLower;
    public int GoldUpper;

    void Start()
    {
        SetStatus();
    }

    ////////////////////////////////////////////////////////////////////////////
    // utils getter

    Backpack backpack
    {
        get { return GameObject.Find("Backpack").GetComponent<Backpack>(); }
    }

    GameControl GameControl
    {
        get { return GameObject.Find("GameController").GetComponent<GameControl>(); }
    }

    ////////////////////////////////////////////////////////////////////////////

    void SetStatus()
    {
        int wave = GameControl.CurrentWave;
        SetMaxHP(BaseHP + GrowHP * wave);
        ATK = BaseATK + GrowATK * wave;
        DEF = BaseDEF + GrowDEF * wave;
    }

    void DropGold()
    {
        int wave = GameControl.CurrentWave;
        float lower = GoldLower * ((wave - 1) / 10 + 1);
        float upper = GoldUpper * ((wave - 1) / 10 + 1);
        int got = Mathf.RoundToInt(Random.Range(lower, upper));
        backpack.GetGold(got);
    }

    public override void OnDie()
    {
        GameControl.CurrentMonsterNumber--;
        DropGold();
        Destroy(gameObject);
    }
}
