using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommonAttackSkillObject : SkillObject
{
    private HashSet<GameObject> hashset = new HashSet<GameObject>();

    [Header("Basic Parameters")]
    public float rate;

    public float EndTime;

    void Start()
    {
        SkillCollider = transform.GetComponent<BoxCollider2D>();
        EndTime = 1.0f;
        rate = 1.0f;
        attack = transform.parent.GetComponent<CharacterBasicLogic>().ATK;
        CalculateSkillDamage();
    }

    void Update()
    {
        EndTime -= Time.deltaTime;
        if (EndTime <= 0)
            Destroy(gameObject);
    }

    private void OnTriggerStay2D(Collider2D other)
    {
        if ((1 << other.gameObject.layer) == MonsterLayerMask.value)
        {
            if (other.gameObject.transform.parent == null)
            {
                if (!hashset.Contains(other.gameObject))
                {
                    hashset.Add(other.gameObject);
                    other.gameObject.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
                }
            }
        }
    }

    public override void CalculateSkillDamage()
    {
        damage = attack;
    }
}
