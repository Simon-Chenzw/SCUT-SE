using System.Collections;
using UnityEngine;

public class BootHandle : MonoBehaviour
{
    // ���뵭������Ķ���ʦ���
    [SerializeField]
    private Animator fadeAnimator = null;

    void Start() { }

    void Update()
    {
        if (Input.anyKeyDown)
        {
            fadeAnimator.SetTrigger("FadeOut");
        }
    }
}
