using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameControl : MonoBehaviour
{
    [Header("Game Settings")]
    public float RefreshInterval = 30.0f;
    public GameObject SpawnPoints;

    [Header("Game Status")]
    public int CurrentWave = 0;
    public int CurrentMonsterNumber = 0;
    public float LastRefreshTime = 0.0f;
    public float CurrentTime = 0.0f;
    public bool IsPause = false;
    public bool IsBossAppear = false;

    void Update()
    {
        if (Input.GetKeyUp(GlobalSetting.ExitKey))
        {
            Application.Quit();
        }

        if (IsPause)
            return;
        CurrentTime += Time.deltaTime;
        if (IsBossAppear) { }
        else if (CurrentTime - LastRefreshTime > RefreshInterval || CurrentMonsterNumber <= 0)
        {
            LastRefreshTime = CurrentTime;
            CurrentWave++;
            if (CurrentWave == 25)
            {
                IsBossAppear = true;
                return;
            }
            for (int i = 0; i < SpawnPoints.transform.childCount; i++)
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
}
