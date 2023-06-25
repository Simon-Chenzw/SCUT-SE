using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireSkillObject : SkillObject
{
    private HashSet<GameObject> hashset = new HashSet<GameObject>();

    public float rate;

    public float EndTime;

    void Start()
    {
        SkillCollider = transform.GetComponent<BoxCollider2D>();
        rate = 2.0f;
        attack = transform.parent.GetComponent<CharacterBasicLogic>().ATK;
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
        if ((1 << other.gameObject.layer) == GlobalSetting.MonsterLayerMask.value)
        {
            if (other.gameObject.transform.parent == null)
                return;
            GameObject tmp = other.gameObject.transform.parent.gameObject;
            if (!hashset.Contains(tmp))
            {
                hashset.Add(tmp);
                tmp.GetComponent<MonsterBasicLogic>().TakeDamage(damage);
            }
        }
    }

    public override void CalculateSkillDamage()
    {
        damage = attack * rate;
    }
}
