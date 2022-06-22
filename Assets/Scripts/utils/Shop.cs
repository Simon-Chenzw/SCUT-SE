using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Shop : MonoBehaviour, IPointerClickHandler
{
    public GameObject SkillChoice;
    public int FreshCost;
    private int CurrentFreshCost;

    private Item[] AllSkill;
    private Item[] AllBuff;

    void Start()
    {
        AllSkill = Resources.LoadAll<Item>("SkillItem");
        AllBuff = Resources.LoadAll<Item>("BuffItem");
        CurrentFreshCost = FreshCost;
        Refresh();
        Display();
    }

    public void OnPointerClick(PointerEventData eventData)
    {
        GameObject go = eventData.pointerCurrentRaycast.gameObject;
        Debug.Log("Clicked: " + go.name);
        if (go.name == "Refresh")
        {
            if (backpack.Pay(CurrentFreshCost))
            {
                CurrentFreshCost *= 2;
                Refresh();
                Display();
            }
        }
        else if (go.name == "SkillSwap")
        {
            backpack?.SwapSkill();
            Display();
        }
        else if (go.name == "Exit")
        {
            globalGameController?.OnShopOut();
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // WorkFlow

    private SkillItem CurrentChoice;

    public void ChoiceSkillPositon(SkillItem item)
    {
        CurrentChoice = item;
        SkillChoice.SetActive(true);
    }

    public void ChoiceOne()
    {
        backpack.ReplaceSkill(CurrentChoice, 0);
        Display();
        SkillChoice.SetActive(false);
    }

    public void ChoiceTwo()
    {
        backpack.ReplaceSkill(CurrentChoice, 1);
        Display();
        SkillChoice.SetActive(false);
    }

    public void Display()
    {
        GameObject.Find("GoldNumberInShop").GetComponent<Text>().text = backpack
            .GetGold()
            .ToString();
        foreach (ShopItem item in items)
        {
            item.Display();
        }
    }

    void Refresh()
    {
        foreach (ShopItem item in items)
        {
            item.Refresh();
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // getter
    ShopItem[] items
    {
        get { return FindObjectsOfType<ShopItem>(); }
    }

    GlobalGameControl globalGameController
    {
        get { return GameObject.Find("GlobalGameController")?.GetComponent<GlobalGameControl>(); }
    }

    Backpack backpack
    {
        get { return GameObject.Find("Backpack")?.GetComponent<Backpack>(); }
    }

    public Item[] GetAllSkill()
    {
        return AllSkill;
    }

    public Item[] GetAllBuff()
    {
        return AllBuff;
    }
}
