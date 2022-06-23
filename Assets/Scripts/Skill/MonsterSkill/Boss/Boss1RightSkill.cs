using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Boss1RightSkill", menuName = "Skill/Enemy/Boss1RightSkill")]
public class Boss1RightSkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "Boss1RightSkill"; }
    }
    public override float GlobalCD
    {
        get { return 2.0f; }
    }
    public override float CD
    {
        get { return 5.0f; }
    }

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(bounds.center.x - bounds.size.x * 4, bounds.center.y, 0);
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/Boss1RightSkill");
        GameObject.Instantiate(SkillObject, position, transform.rotation, transform);
    }

    public override bool CheckUseSkill(
        Bounds bounds,
        Transform OurTransform,
        Transform EnemyTransform
    )
    {
        float distance = Mathf.Sqrt(
            Mathf.Pow(OurTransform.position.x - EnemyTransform.position.x, 2.0f)
                + Mathf.Pow(OurTransform.position.y - EnemyTransform.position.y, 2.0f)
        );
        float SkillDistance = bounds.size.x * 15f;
        if (SkillDistance >= distance)
            return true;
        else
            return false;
    }
}
