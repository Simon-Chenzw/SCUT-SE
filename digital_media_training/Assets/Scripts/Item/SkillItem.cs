using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 包含一个 Skill 类型的 Item
/// </summary>
[CreateAssetMenu(fileName = "SkillItem", menuName = "Item/Skill")]
public class SkillItem : Item
{
    [Header("Skill Settings")]
    public CharacterSkill skill;
}
