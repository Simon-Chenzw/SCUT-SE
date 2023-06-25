using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommonEnemy4AttackSkillObject : SkillObject
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

    void Update()
    {
        EndTime -= Time.deltaTime;
        if (EndTime <= 0)
            Destroy(gameObject);
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
                    GameObject tmp = gameObject.transform.parent.gameObject;
                    tmp.GetComponent<MonsterBasicLogic>().OnDie();
                }
            }
        }
    }

    public override void CalculateSkillDamage()
    {
        damage = attack * rate;
    }
}
