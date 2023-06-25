using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(
    fileName = "SuperEnemy2CommonAttackSkill",
    menuName = "Skill/Enemy/SuperEnemy2CommonAttackSkill"
)]
public class SuperEnemy2CommonAttackSkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "SuperEnemy2CommonAttackSkill"; }
    }
    public override float GlobalCD
    {
        get { return 2.0f; }
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
        GameObject SkillObject = Resources.Load<GameObject>(
            "SkillRange/SuperEnemy2CommonAttackSkill"
        );
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
        float SkillDistance = bounds.size.x * 3.0f;
        if (SkillDistance >= distance)
            return true;
        else
            return false;
    }
}
