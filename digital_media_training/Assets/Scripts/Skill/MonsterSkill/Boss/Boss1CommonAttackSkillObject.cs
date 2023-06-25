using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss1CommonAttackSkillObject : SkillObject
{
    private HashSet<GameObject> hashset = new HashSet<GameObject>();

    public float rate;

    public float EndTime;

    void Start()
    {
        SkillCollider = transform.GetComponent<BoxCollider2D>();
        rate = 1.0f;
        attack = transform.parent.GetComponent<MonsterBasicLogic>().ATK;
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
