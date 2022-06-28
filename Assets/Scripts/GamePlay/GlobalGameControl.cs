using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GlobalGameControl : MonoBehaviour
{
    [Header("Game Settings")]
    public string[] LevelFileName;

    [Header("Game Status")]
    public int CurrentLevel = 0;
    public int GlobalWave;
    public bool IsShopping = false;

    void Start()
    {
        DontDestroyOnLoad(gameObject);
    }

    public void OnNextLevel()
    {
        if (CurrentLevel == LevelFileName.GetLength(0)) // 通关时，进入游戏结束场景
        {
            SceneManager.LoadScene("Scenes/GameOverMenu", LoadSceneMode.Single);
            Destroy(gameObject);
        }
        else
        {
            SceneManager.LoadScene("Scenes/" + LevelFileName[CurrentLevel], LoadSceneMode.Single);
            CurrentLevel++;
        }
    }

    public void OnNextWave()
    {
        GlobalWave++;
    }

    public void OnShopIn()
    {
        GameObject.Find("Character").GetComponent<CharacterBasicLogic>().MakeHPFull();
        GameObject.Find("Main Camera").GetComponent<AudioListener>().enabled = false;
        IsShopping = true;
        SceneManager.LoadScene("Scenes/Shop", LoadSceneMode.Additive);
    }

    public void OnShopOut()
    {
        IsShopping = false;
        SceneManager.UnloadSceneAsync("Scenes/Shop");
        GameObject.Find("Main Camera").GetComponent<AudioListener>().enabled = true;
    }
}
