using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterBasicLogic : BasicLogic
{
    [Header("Settings")]
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

    GlobalGameControl GlobalGameController
    {
        get { return GameObject.Find("GlobalGameController").GetComponent<GlobalGameControl>(); }
    }

    GameControl GameController
    {
        get { return GameObject.Find("GameController").GetComponent<GameControl>(); }
    }

    ////////////////////////////////////////////////////////////////////////////

    private void SetStatus()
    {
        int Wave = GlobalGameController.GlobalWave;
        float Scale = (Wave - 1) / 10.0f + 1;
        SetMaxHP(Mathf.RoundToInt(BaseHP * Scale));
        SetATK(BaseATK * Scale);
        SetDEF(BaseDEF * Scale);
    }

    private void DropGold()
    {
        int Wave = GlobalGameController.GlobalWave;
        float lower = GoldLower * ((Wave - 1) / 10.0f + 1);
        float upper = GoldUpper * ((Wave - 1) / 10.0f + 1);
        int got = Mathf.RoundToInt(Random.Range(lower, upper));
        backpack.GetGold(got);
    }

    public override void OnDie()
    {
        GameController.CurrentMonsterNumber--;
        DropGold();
        Destroy(gameObject);
    }
}
