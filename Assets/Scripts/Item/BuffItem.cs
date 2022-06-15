using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 包含一个 Buff 的 Item
/// </summary>
[CreateAssetMenu(fileName = "BuffItem", menuName = "Item/Buff")]
public class BuffItem : Item
{
    public string BuffItemName;
    public int HpAddSetting;
    public float HpMulSetting;
    public float AtkAddSetting;
    public float AtkMulSetting;
    public float DefAddSetting;
    public float DefMulSetting;
    public float VulnerableSetting;

    public override string ItemName
    {
        get { return BuffItemName; }
    }

    public override string ItemType
    {
        get { return "Buff"; }
    }

    public override int HpAdd
    {
        get { return HpAddSetting; }
    }

    public override float HpMul
    {
        get { return HpMulSetting; }
    }

    public override float AtkAdd
    {
        get { return AtkAddSetting; }
    }

    public override float AtkMul
    {
        get { return AtkMulSetting; }
    }

    public override float DefAdd
    {
        get { return DefAddSetting; }
    }

    public override float DefMul
    {
        get { return DefMulSetting; }
    }

    public override float Vulnerable
    {
        get { return VulnerableSetting; }
    }
}
