using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "CommonAttackSkill", menuName = "Skill/Character/CommonAttackSkill")]
public class CommonAttackSkill : Skill
{
    public override string SkillName
    {
        get { return "CommonAttack"; }
    }
    public override float GlobalCD
    {
        get { return 0.5f; }
    }
    public override float CD
    {
        get { return 0.5f; }
    }

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(0, 0, 0);
        if (transform.GetChild(0).localScale.x > 0)
        {
            position = new Vector3(bounds.center.x + bounds.size.x, bounds.center.y, 0);
        }
        else
        {
            position = new Vector3(bounds.center.x - bounds.size.x, bounds.center.y, 0);
        }
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/CommonAttack");
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
