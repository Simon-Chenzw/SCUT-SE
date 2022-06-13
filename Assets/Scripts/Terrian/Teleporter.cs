using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Teleporter : MonoBehaviour
{
    public LayerMask CharacterLayerMask; // 主角层

    private void OnTriggerStay2D(Collider2D other)
    {
        // 确保碰撞到的是主角的根物体
        if (
            (1 << other.gameObject.layer) != CharacterLayerMask
            || other.gameObject.transform.parent != null
            || !other.GetComponent<CharacterMovement>().NeedTeleport
        )
            return;

        // 根据朝向，施加传送后的偏移
        Vector3 Offest = new Vector3(other.bounds.extents.x, 0.0f, 0.0f);
        if (other.gameObject.transform.localScale.x < 0)
        {
            Offest = -Offest;
        }
        if (name == "Left")
        {
            other.gameObject.transform.position =
                transform.parent.Find("Right").transform.position + Offest;
        }
        else if (name == "Right")
        {
            other.gameObject.transform.position =
                transform.parent.Find("Left").transform.position - Offest;
        }

        other.GetComponent<CharacterMovement>().NeedTeleport = false; // 清除传送标记
    }
}
