using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(
    fileName = "CommonEnemy4AttackSkill",
    menuName = "Skill/Enemy/CommonEnemy4AttackSkill"
)]
public class CommonEnemy4AttackSkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "CommonEnemy4AttackSkill"; }
    }
    public override float GlobalCD
    {
        get { return 0.0f; }
    }
    public override float CD
    {
        get { return 0.0f; }
    }

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(0, 0, 0);
        position = new Vector3(bounds.center.x, bounds.center.y, 0);
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/CommonEnemy4Attack");
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
        float SkillDistance = bounds.size.x * 2.5f;
        if (SkillDistance >= distance)
            return true;
        else
            return false;
    }
}
