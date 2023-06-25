using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Level1Music : MonoBehaviour
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
        if (GameObject.Find("Boss1(Clone)") != null && MusicChange != true)
        {
            boss = Resources.Load<AudioClip>("Music/battle1");
            ;
            music.clip = boss;
            music.Play();
            MusicChange = true;
        }
    }
}
