using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Boss1LeftSkill", menuName = "Skill/Enemy/Boss1LeftSkill")]
public class Boss1LeftSkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "Boss1LeftSkill"; }
    }
    public override float GlobalCD
    {
        get { return 2.0f; }
    }
    public override float CD
    {
        get { return 5.0f; }
    }
    private AudioSource music;
    private AudioClip AttackMusic;

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(bounds.center.x - bounds.size.x * 5, bounds.center.y, 0);
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/Boss1LeftSkill");
        GameObject skill = GameObject.Instantiate(
            SkillObject,
            position,
            transform.rotation,
            transform
        );
        GameObject Parent = skill.transform.parent.gameObject;
        if (Parent.GetComponent<AudioSource>() == null)
            music = Parent.AddComponent<AudioSource>();
        AttackMusic = Resources.Load<AudioClip>("Music/Bow1");
        music.clip = AttackMusic;
        music.Play();
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
