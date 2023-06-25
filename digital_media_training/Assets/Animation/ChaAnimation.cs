using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChaAnimation : MonoBehaviour
{
    Animator animator;
    static public KeyCode AttackKey = GlobalSetting.CommonAttackKey;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        AniInit();
        AniUpdate();
    }

    void AniInit()
    {
        animator.SetBool("Running", false);
        animator.SetBool("Jumping", false);
        animator.SetBool("Attack", false);
    }

    void AniUpdate()
    {
        if (Input.GetAxis("Horizontal") != 0)
        {
            animator.SetBool("Running", true);
        }
        if (Input.GetAxis("Jump") != 0)
        {
            animator.SetBool("Jumping", true);
        }
        if (Input.GetKey(AttackKey) == true)
        {
            animator.SetBool("Attack", true);
        }
    }
}
