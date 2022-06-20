using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(
    fileName = "CommonEnemy5AttackSkill",
    menuName = "Skill/Enemy/CommonEnemy5AttackSkill"
)]
public class CommonEnemy5AttackSkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "CommonEnemy5AttackSkill"; }
    }
    public override float GlobalCD
    {
        get { return 5.0f; }
    }
    public override float CD
    {
        get { return 5.0f; }
    }

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(0, 0, 0);
        position = new Vector3(bounds.center.x, bounds.center.y, 0);
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/CommonEnemy5Attack");
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
        float SkillDistance = bounds.size.x * 25;
        if (SkillDistance >= distance)
            return true;
        else
            return false;
    }
}
