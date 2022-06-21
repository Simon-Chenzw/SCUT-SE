using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommonManaAttackSkillObject : SkillObject
{
    private Rigidbody2D SkillRigidbody;

    [Header("Basic Parameters")]
    public float rate;

    public float MoveSpeed;

    void Start()
    {
        SkillCollider = transform.GetComponent<BoxCollider2D>();
        SkillRigidbody = transform.GetComponent<Rigidbody2D>();
        attack = transform.parent.GetComponent<CharacterBasicLogic>().ATK;
        rate = 1.0f;
        if (transform.parent.Find("LogicBody").transform.localScale.x > 0)
            SkillRigidbody.velocity = new Vector2(MoveSpeed, 0);
        else
            SkillRigidbody.velocity = new Vector2(-MoveSpeed, 0);
        CalculateSkillDamage();
    }

    private GameObject target;

    private void OnTriggerEnter2D(Collider2D other)
    {
        GameObject User = transform.parent.gameObject;
        if (target != null)
            return;
        if (
            (other.gameObject.layer) == User.layer
            || ((1 << other.gameObject.layer) == GlobalSetting.TeleporterLayerMask)
        )
        {
            return;
        }
        else if (
            (1 << other.gameObject.layer) == GlobalSetting.MonsterLayerMask
            || (1 << other.gameObject.layer) == GlobalSetting.CharacterLayerMask
        )
        {
            if (other.gameObject.transform.parent == null)
            {
                other.gameObject.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
            }
            else if (other.gameObject.name == "LogicBody")
            {
                GameObject tmp = other.gameObject.transform.root.gameObject;
                target = tmp;
                tmp.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
                Destroy(gameObject);
            }
        }
        Destroy(gameObject);
    }

    public override void CalculateSkillDamage()
    {
        damage = attack * rate;
    }
}
