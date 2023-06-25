using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnControl : MonoBehaviour
{
    public int NeedToSpawnCommon = 0;
    public int NeedToSpawnSuper = 0;
    public bool NeedToSpawnBoss = false;

    public GameObject[] CommonMonster;
    public GameObject[] SuperMonster;
    public GameObject BossMonster;

    void Update()
    {
        if (NeedToSpawnCommon > 0)
        {
            if (CanSpawn())
            {
                Instantiate(
                    CommonMonster[Random.Range(0, CommonMonster.Length)],
                    gameObject.transform.position,
                    gameObject.transform.rotation
                );
                NeedToSpawnCommon--;
            }
        }
        else if (NeedToSpawnSuper > 0)
        {
            if (CanSpawn())
            {
                Instantiate(
                    SuperMonster[Random.Range(0, SuperMonster.Length)],
                    gameObject.transform.position,
                    gameObject.transform.rotation
                );
                NeedToSpawnSuper--;
            }
        }
        else if (NeedToSpawnBoss)
        {
            Instantiate(BossMonster, gameObject.transform.position, gameObject.transform.rotation);
            NeedToSpawnBoss = false;
        }
    }

    private bool CanSpawn()
    {
        RaycastHit2D MonsterDetect = Physics2D.Raycast(
            gameObject.transform.position,
            Vector2.down,
            1.0f,
            GlobalSetting.MonsterLayerMask
        );
        return MonsterDetect.collider == null;
    }
}
