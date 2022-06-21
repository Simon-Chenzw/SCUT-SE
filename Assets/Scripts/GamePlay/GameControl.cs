using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameControl : MonoBehaviour
{
    [Header("Game Settings")]
    public float RefreshInterval = 30.0f; // 两波之间的最大时间间隔
    public GameObject SpawnPoints; // 怪物生成点

    [Header("Game Status")]
    public int CurrentWave = 0; // 当前波数
    public int CurrentMonsterNumber = 0; // 当前存活怪物数量（不包括Boss）
    public float LastRefreshTime = 0.0f; // 最后刷新时间
    public float CurrentTime = 0.0f; // 当前时间
    public bool IsPause = false; // 是否正在暂停
    public bool IsBossExist = false; // Boss是否存在

    private bool HaveBeenToShop = false; // 当前5波是否去过商店

    void Update()
    {
        if (Input.GetKeyUp(GlobalSetting.ExitKey))
        {
            Application.Quit();
        }

        // 测试用，秒杀所有怪物
        if (Input.GetKeyDown(GlobalSetting.KillAllMonsters))
        {
            MonsterBasicLogic[] Monsters = FindObjectsOfType<MonsterBasicLogic>();
            foreach (MonsterBasicLogic Monster in Monsters)
            {
                Monster.OnDie();
            }
        }

        // 若当前处于暂停或处于商店，停止关卡逻辑
        if (IsPause || GlobalGameController.IsShopping)
            return;
        CurrentTime += Time.deltaTime;

        if (IsBossExist) // Boss存在时，等待Boss死亡
        {
            // 若场上还有怪物，说明Boss没死
            if (CurrentMonsterNumber > 0)
                return;
            GlobalGameController.OnNextLevel(); // 进入下一关
            return;
        }

        if (CurrentWave == 24) // 到达第24波时，等待Boss出现
        {
            // 若场上还有怪物，先不出现Boss
            if (CurrentMonsterNumber > 0)
                return;
            SpawnPoints.transform.GetChild(0).GetComponent<SpawnControl>().NeedToSpawnBoss = true;
            CurrentMonsterNumber++;
            IsBossExist = true;
            LastRefreshTime = CurrentTime;
            CurrentWave++;
            GameObject.Find("WaveNumber").GetComponent<Text>().text = CurrentWave.ToString();
            GlobalGameController.OnNextWave();
            return;
        }

        if (GlobalGameController.GlobalWave > 0 && CurrentWave % 5 == 0 && !HaveBeenToShop) // 不处于游戏刚开始，且波数是5的倍数，且当前5波没去过商店时，进入商店
        {
            // 若场上还有怪物，先不进入商店
            if (CurrentMonsterNumber > 0)
                return;
            HaveBeenToShop = true;
            GlobalGameController.OnShopIn();
            return;
        }

        if (CurrentTime - LastRefreshTime > RefreshInterval || CurrentMonsterNumber == 0) // 超过刷怪时间或怪物杀完时，进入下一波
        {
            LastRefreshTime = CurrentTime;
            CurrentWave++;
            GameObject.Find("WaveNumber").GetComponent<Text>().text = CurrentWave.ToString();
            GlobalGameController.OnNextWave();
            HaveBeenToShop = false;

            // 生成小怪
            for (int i = 1; i < SpawnPoints.transform.childCount; i++)
            {
                SpawnPoints.transform.GetChild(i).GetComponent<SpawnControl>().NeedToSpawnCommon +=
                    GlobalSetting.SpawnMonsterNumer[CurrentWave - 1][0];
                SpawnPoints.transform.GetChild(i).GetComponent<SpawnControl>().NeedToSpawnSuper +=
                    GlobalSetting.SpawnMonsterNumer[CurrentWave - 1][1];
                CurrentMonsterNumber +=
                    GlobalSetting.SpawnMonsterNumer[CurrentWave - 1][0]
                    + GlobalSetting.SpawnMonsterNumer[CurrentWave - 1][1];
            }
        }
    }

    GlobalGameControl GlobalGameController
    {
        get { return GameObject.Find("GlobalGameController").GetComponent<GlobalGameControl>(); }
    }
}
