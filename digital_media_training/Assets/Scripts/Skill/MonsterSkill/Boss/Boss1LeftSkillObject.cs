using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss1LeftSkillObject : SkillObject
{
    private Rigidbody2D SkillRigidbody;
    private HashSet<GameObject> hashset = new HashSet<GameObject>();

    [Header("Basic Parameters")]
    public float rate;

    public float MoveSpeed = 1.5f;

    void Start()
    {
        SkillRigidbody = transform.GetComponent<Rigidbody2D>();
        attack = transform.parent.GetComponent<MonsterBasicLogic>().ATK;
        rate = 2.0f;
        SkillRigidbody.velocity = new Vector2(-MoveSpeed, -MoveSpeed);
        CalculateSkillDamage();
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if ((1 << other.gameObject.layer) == GlobalSetting.CharacterLayerMask.value)
        {
            if (other.gameObject.transform.parent == null)
            {
                if (!hashset.Contains(other.gameObject))
                {
                    hashset.Add(other.gameObject);
                    other.gameObject.GetComponent<CharacterBasicLogic>().TakeDamage(damage);
                    Destroy(gameObject);
                }
            }
        }
    }

    public override void CalculateSkillDamage()
    {
        damage = attack * rate;
    }
}
