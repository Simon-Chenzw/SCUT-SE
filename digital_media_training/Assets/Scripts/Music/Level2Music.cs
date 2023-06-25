using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Level2Music : MonoBehaviour
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
        if (GameObject.Find("Boss1 Level2(Clone)") != null && MusicChange != true)
        {
            boss = Resources.Load<AudioClip>("Music/04 The ancient evil");
            ;
            music.clip = boss;
            music.Play();
            MusicChange = true;
        }
    }
}
