using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SuperEnemy2CommonAttackSkillObject : SkillObject
{
    private HashSet<GameObject> hashset = new HashSet<GameObject>();

    public float rate;

    public float EndTime;

    void Start()
    {
        music = gameObject.AddComponent<AudioSource>();
        AttackMusic = Resources.Load<AudioClip>("Music/Battleaxe1");
        music.clip = AttackMusic;
        music.Play();
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

    private void OnTriggerStay2D(Collider2D other)
    {
        if ((1 << other.gameObject.layer) == GlobalSetting.CharacterLayerMask.value)
        {
            if (other.gameObject.transform.parent == null)
            {
                if (!hashset.Contains(other.gameObject))
                {
                    hashset.Add(other.gameObject);
                    other.gameObject.GetComponent<CharacterBasicLogic>().TakeDamage(damage);
                }
            }
        }
    }

    public override void CalculateSkillDamage()
    {
        damage = attack * rate;
    }
}
