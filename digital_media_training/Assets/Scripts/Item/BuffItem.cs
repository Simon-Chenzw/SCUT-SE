using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 包含一个 Buff 的 Item
/// </summary>
[CreateAssetMenu(fileName = "BuffItem", menuName = "Item/Buff")]
public class BuffItem : Item
{
    [Header("Buff Settings")]
    public int HpAdd;
    public float HpMul;
    public float AtkAdd;
    public float AtkMul;
    public float DefAdd;
    public float DefMul;
    public float Vulnerable;
}
