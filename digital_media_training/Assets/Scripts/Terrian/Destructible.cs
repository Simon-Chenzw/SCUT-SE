using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Destructible : MonoBehaviour
{
    [Header("Settings")]
    public bool CanReborn = false;
    public float RebornInterval = 10.0f;

    [Header("Status")]
    public bool Reborning = false;
    public float RebornCountdown;

    void Update()
    {
        if (Reborning)
        {
            RebornCountdown -= Time.deltaTime;
            if (RebornCountdown <= 0)
            {
                gameObject.GetComponent<MeshRenderer>().enabled = true;
                gameObject.GetComponent<BoxCollider2D>().enabled = true;
                Reborning = false;
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if ((1 << other.gameObject.layer) == GlobalSetting.SkillLayerMask)
        {
            gameObject.GetComponent<MeshRenderer>().enabled = false;
            gameObject.GetComponent<BoxCollider2D>().enabled = false;
            if (CanReborn)
            {
                RebornCountdown = RebornInterval;
                Reborning = true;
            }
        }
    }
}
