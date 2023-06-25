using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "BigHitSkill", menuName = "Skill/Character/BigHitSkill")]
public class BigHitSkill : CharacterSkill
{
    public override string SkillName
    {
        get { return "BigHitSkill"; }
    }
    public override float GlobalCD
    {
        get { return 1.0f; }
    }
    public override float CD
    {
        get { return 5.0f; }
    }

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(0, 0, 0);
        if (transform.Find("LogicBody").localScale.x > 0)
        {
            position = new Vector3(bounds.max.x + bounds.size.x, bounds.center.y, 0);
        }
        else
        {
            position = new Vector3(bounds.min.x - bounds.size.x, bounds.center.y, 0);
        }
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/BigHitSkill");
        GameObject.Instantiate(SkillObject, position, transform.rotation, transform);
    }

    public override bool CheckUseSkill(
        Bounds bounds,
        Transform OurTransform,
        Transform EnemyTransform
    )
    {
        return false;
    }
}
