using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommonAttack : SkillBase
{
    private Collider2D SkillCollider;

    // public LayerMask MonsterLayerMask; //


    public float rate; //

    public float damage; //

    private HashSet<GameObject> hashset = new HashSet<GameObject>();

    public float EndTime;

    void Start()
    {
        SkillCollider = transform.GetComponent<BoxCollider2D>();
        EndTime = 0.1f;
        rate = 0.1f;
        attack = transform.parent.GetComponent<CharacterBasicLogic>().ATK;
        SkillDamage();
    }

    void Update()
    {
        if (EndTime > 0)
        {
            EndTime -= Time.deltaTime;
            if (EndTime <= 0)
            {
                Destroy(gameObject);
                if (hashset.Count > 0)
                {
                    foreach (var item in hashset)
                    {
                        Debug.Log("renne");
                        item.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
                    }
                    hashset.Clear();
                }
            }
        }
    }

    void OnTriggerStay2D(Collider2D other)
    {
        //mask
        if ((1 << other.gameObject.layer) == MonsterLayerMask.value)
        {
            if (other.gameObject.transform.parent == null)
            {
                if (hashset.Contains(other.gameObject) == false)
                {
                    hashset.Add(other.gameObject);
                }
            }
        }
    }

    public override void UseSkill() { }

    public override void SkillDamage()
    {
        damage = attack * rate;
    }
}
