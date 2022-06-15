using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// BuffItem
/// 多个 Buff 的乘算增益是先加再乘，所以没有效果是 0.0
/// </summary>
public class Item : ScriptableObject
{
    /// 非虚基类，但无效果
    public string ItemName
    {
        get { return "BaseItem"; }
    }

    public Skill Skill
    {
        get { return null; }
    }

    public int HpAdd
    {
        get { return 0; }
    }

    public float HpMul
    {
        get { return 0.0f; }
    }

    public float AtkAdd
    {
        get { return 0.0f; }
    }

    public float AtkMul
    {
        get { return 0.0f; }
    }

    public float DefAdd
    {
        get { return 0.0f; }
    }

    public float DefMul
    {
        get { return 0.0f; }
    }

    public float Vulnerable
    {
        get { return 0.0f; }
    }
}
