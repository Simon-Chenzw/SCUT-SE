using UnityEngine;
using UnityEngine.SceneManagement;

public class TransitionHandler : MonoBehaviour
{
    // ���ڼ��س�������
    [SerializeField]
    private string nextScene = "";

    // ���õ��붯����־
    [SerializeField]
    private bool disableFadeInAnimation = false;

    private void Start()
    {
        if (disableFadeInAnimation)
        {
            // �����붯���Ƶ�ĩβ
            Animator animator = gameObject.GetComponent<Animator>();
            animator.Play("FadeIn", 0, 1);
        }
    }

    // �ӵ�����������ʱ����
    void FadeOutFinished()
    {
        // ��һ�������ļ���
        SceneManager.LoadScene(nextScene);
    }
}
