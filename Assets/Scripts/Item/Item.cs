using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// BuffItem 虚基类，但部分接口都有默认实现。
/// 多个 Buff 的乘算增益是先加再乘，所以没有效果是 0.0f 。
/// </summary>
public abstract class Item : ScriptableObject
{
    public virtual string ItemName { get; }

    /// <summary>
    /// 返回值: "Skill" "Buff"
    /// </summary>
    public virtual string ItemType { get; }

    public virtual Skill Skill
    {
        get { return null; }
    }

    public virtual int HpAdd
    {
        get { return 0; }
    }

    public virtual float HpMul
    {
        get { return 0.0f; }
    }

    public virtual float AtkAdd
    {
        get { return 0.0f; }
    }

    public virtual float AtkMul
    {
        get { return 0.0f; }
    }

    public virtual float DefAdd
    {
        get { return 0.0f; }
    }

    public virtual float DefMul
    {
        get { return 0.0f; }
    }

    public virtual float Vulnerable
    {
        get { return 0.0f; }
    }
}
