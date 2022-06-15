using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 包含一个 Skill 类型的 Item
/// </summary>
[CreateAssetMenu(fileName = "SkillItem", menuName = "Item/Skill")]
public class SkillItem : Item
{
    public string SkillItemName;
    public Skill skill;

    public override string ItemName
    {
        get { return SkillItemName; }
    }

    public override string ItemType
    {
        get { return "Skill"; }
    }

    public override Skill Skill
    {
        get { return skill; }
    }
}
