using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Teleporter : MonoBehaviour
{
    private void OnTriggerStay2D(Collider2D other)
    {
        // 确保碰撞到的是主角的根物体
        if (
            (1 << other.gameObject.layer) != GlobalSetting.CharacterLayerMask
            || other.gameObject.transform.parent != null
            || !other.GetComponent<CharacterMovement>().NeedTeleport
        )
            return;

        if (name == "PortA")
        {
            other.gameObject.transform.position = transform.parent.Find("PortB").transform.position;
        }
        else if (name == "PortB")
        {
            other.gameObject.transform.position = transform.parent.Find("PortA").transform.position;
        }

        other.GetComponent<CharacterMovement>().NeedTeleport = false; // 清除传送标记
    }
}
