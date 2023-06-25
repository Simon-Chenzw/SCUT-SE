using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Level3Music : MonoBehaviour
{
    private AudioClip boss;
    private AudioSource music;

    private bool MusicChange = false;

    public void Start()
    {
        music = gameObject.GetComponent<AudioSource>();
    }

    void Update()
    {
        if (GameObject.Find("Boss1 Level3(Clone)") != null && MusicChange != true)
        {
            boss = Resources.Load<AudioClip>("Music/01 Riding dragons");
            ;
            music.clip = boss;
            music.Play();
            MusicChange = true;
        }
    }
}
