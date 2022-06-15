using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnControl : MonoBehaviour
{
    public int NeedToSpawnCommon = 0;
    public int NeedToSpawnSuper = 0;

    public GameObject CommonMonster;
    public GameObject SuperMonster;

    void Update()
    {
        if (NeedToSpawnCommon > 0)
        {
            if (CanSpawn())
            {
                Instantiate(
                    CommonMonster,
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
                    SuperMonster,
                    gameObject.transform.position,
                    gameObject.transform.rotation
                );
                NeedToSpawnSuper--;
            }
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
