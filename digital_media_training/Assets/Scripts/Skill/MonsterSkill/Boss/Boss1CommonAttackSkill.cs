using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(
    fileName = "Boss1CommonAttackSkill",
    menuName = "Skill/Enemy/Boss1CommonAttackSkill"
)]
public class Boss1CommonAttackSkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "Boss1CommonAttackSkill"; }
    }
    public override float GlobalCD
    {
        get { return 1.0f; }
    }
    public override float CD
    {
        get { return 1.0f; }
    }

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        GameObject SkillObject = Resources.Load<GameObject>(
            "SkillRange/Boss1CommonAttackSkillEmpty"
        );
        Vector3 position = transform.position;
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
        float SkillDistance = bounds.size.x * 2;
        if (SkillDistance >= distance)
            return true;
        else
            return false;
    }
}
