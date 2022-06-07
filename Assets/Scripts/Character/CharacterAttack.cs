using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterAttack : MonoBehaviour
{
    public GameObject CommonAttackRange;

    public GameObject tmp;
    static private KeyCode AttackKey = KeyCode.J;

    private Collider2D CharacterCollider;
    private Rigidbody2D CharacterRigidbody;

    public float Attack;

    void Start()
    {
        CharacterRigidbody = transform.GetComponent<Rigidbody2D>();
        CharacterCollider = transform.GetChild(0).GetChild(0).GetComponent<BoxCollider2D>();
        Attack = gameObject.GetComponent<CharacterBasicLogic>().ATK;
    }

    void UseSkill()
    {
        if (Input.GetKeyDown(AttackKey))
        {
            Vector3 position = new Vector3(0, 0, 0);
            if (transform.localScale.x > 0)
            {
                position = new Vector3(
                    CharacterCollider.bounds.center.x + CharacterCollider.bounds.size.x,
                    CharacterCollider.bounds.center.y,
                    0
                );
            }
            else
            {
                position = new Vector3(
                    CharacterCollider.bounds.center.x - CharacterCollider.bounds.size.x,
                    CharacterCollider.bounds.center.y,
                    0
                );
            }
            tmp = GameObject.Instantiate(
                CommonAttackRange,
                position,
                transform.rotation,
                gameObject.transform
            );
        }
    }

    void Update()
    {
        UseSkill();
    }
}
