using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Boss1SkySkill", menuName = "Skill/Enemy/Boss1SkySkill")]
public class Boss1SkySkill : MonsterSkill
{
    public override string SkillName
    {
        get { return "Boss1SkySkill"; }
    }
    public override float GlobalCD
    {
        get { return 1.0f; }
    }
    public override float CD
    {
        get { return 1.0f; }
    }

    private AudioSource music;
    private AudioClip AttackMusic;

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/Boss1SkyEmptySkill");
        Vector3 position = new Vector3(0, 13.5f, 0);
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
        float SkillDistance = bounds.size.x * 15;
        if (SkillDistance >= distance)
            return true;
        else
            return false;
    }
}
