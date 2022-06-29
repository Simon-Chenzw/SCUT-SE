using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(
    fileName = "CommonManaAttackSkill",
    menuName = "Skill/Character/CommonManaAttackSkill"
)]
public class CommonManaAttackSkill : CharacterSkill
{
    public override string SkillName
    {
        get { return "CommonManaAttack"; }
    }
    public override float GlobalCD
    {
        get { return 0.5f; }
    }
    public override float CD
    {
        get { return 0.5f; }
    }

    private AudioSource music;
    private AudioClip AttackMusic;

    public override void CreateSkill(Bounds bounds, Transform transform)
    {
        Vector3 position = new Vector3(0, 0, 0);
        position = new Vector3(bounds.center.x, bounds.center.y, 0);
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/CommonManaAttack");
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
        return false;
    }
}
