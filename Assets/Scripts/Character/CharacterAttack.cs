using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterAttack : MonoBehaviour
{
    public GameObject CommonAttackRange;

    public GameObject CommonManaAttackRange;

    private GameObject tmp,
        tmp2;

    private Collider2D CharacterCollider;
    private Rigidbody2D CharacterRigidbody;

    public float del;
    public float Attack;

    void Start()
    {
        CharacterRigidbody = transform.GetComponent<Rigidbody2D>();
        CharacterCollider = transform.GetChild(0).GetChild(0).GetComponent<BoxCollider2D>();
    }

    void CommonAttack()
    {
        Vector3 position = new Vector3(0, 0, 0);
        if (transform.GetChild(0).localScale.x > 0)
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

    void CommonManaAttack()
    {
        Vector3 position = new Vector3(0, 0, 0);
        if (transform.GetChild(0).localScale.x > 0)
        {
            position = new Vector3(
                CharacterCollider.bounds.center.x + CharacterCollider.bounds.size.x * del,
                CharacterCollider.bounds.center.y,
                0
            );
        }
        else
        {
            position = new Vector3(
                CharacterCollider.bounds.center.x - CharacterCollider.bounds.size.x * del,
                CharacterCollider.bounds.center.y,
                0
            );
        }
        tmp2 = GameObject.Instantiate(
            CommonManaAttackRange,
            position,
            transform.rotation,
            gameObject.transform
        );
    }

    void Update()
    {
        if (Input.GetKeyDown(GlobalSetting.AttackKey))
        {
            CommonAttack();
        }
        else if (Input.GetKeyDown(GlobalSetting.ManaAttackKey))
        {
            CommonManaAttack();
        }
    }
}
