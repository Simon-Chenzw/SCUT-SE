using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommonManaAttack : SkillBase
{
    public override void UseSkill() { }

    public override void SkillDamage()
    {
        damage = attack * rate;
    }

    private Collider2D SkillCollider;

    private Rigidbody2D MonsterRigidbody;

    [Header("Basic Parameters")]
    public float damage;
    public float rate;

    public float MoveSpeed;

    void Start()
    {
        SkillCollider = transform.GetComponent<BoxCollider2D>();
        MonsterRigidbody = transform.GetComponent<Rigidbody2D>();
        attack = transform.parent.GetComponent<CharacterBasicLogic>().ATK;
        rate = 1.0f;
        if (transform.parent.GetChild(0).transform.localScale.x > 0)
            MonsterRigidbody.velocity = new Vector2(MoveSpeed, 0);
        else
            MonsterRigidbody.velocity = new Vector2(-MoveSpeed, 0);
        SkillDamage();
    }

    void update() { }

    private GameObject target;

    private void OnTriggerStay2D(Collider2D other)
    {
        GameObject User = transform.parent.gameObject;
        if (target != null)
            return;
        if ((other.gameObject.layer) == User.layer)
        {
            return;
        }
        else if (
            (1 << other.gameObject.layer) == MonsterLayerMask.value
            || (1 << other.gameObject.layer) == CharacterLayerMask.value
        )
        {
            if (other.gameObject.transform.parent == null)
            {
                other.gameObject.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
            }
            else if (other.gameObject.name == "Body")
            {
                GameObject tmp = other.gameObject.transform.root.gameObject;
                target = tmp;
                tmp.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
                Destroy(gameObject);
            }
        }
        Destroy(gameObject);
    }
}
