using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MstAnimation : MonoBehaviour
{
    Animator animator;

    //gameObject pre;

    int hp = 10;

    // Start is called before the first frame update
    void Start()
    {
        //tranform prepre = tranform.root;
        //hp = root.GetComponent<MonsterBasicLogic>().MaxHP;
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        //hp = GetComponent<BasicLogic>().HP;
        if (hp <= 0)
        {
            Debug.Log("died");
            animator.SetBool("Die", true);
        }
    }
}
