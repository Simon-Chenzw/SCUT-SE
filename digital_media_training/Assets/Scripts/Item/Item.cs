using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// BuffItem 虚基类，但部分接口都有默认实现。
/// 多个 Buff 的乘算增益是先加再乘，所以没有效果是 0.0f 。
/// </summary>
public abstract class Item : ScriptableObject
{
    [Header("Item Settings")]
    public string ItemName;

    [TextArea(5, 10)]
    public string ItemDesc;

    public int ItemPrice;

    public int ItemRandomWeight;
}
