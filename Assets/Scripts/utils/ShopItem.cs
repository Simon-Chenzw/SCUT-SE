using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ShopItem : MonoBehaviour, IPointerClickHandler
{
    private Item item;
    public ShopItemBehaviour behaviour;

    void Start()
    {
        Display();
    }

    public void Display()
    {
        if (behaviour == ShopItemBehaviour.DisplaySkillOne)
        {
            item = backpack?.SkillItemOne;
        }
        else if (behaviour == ShopItemBehaviour.DisplaySkillTwo)
        {
            item = backpack?.SkillItemTwo;
        }

        if (item != null)
        {
            TextName.text = item.ItemName;
            TextDesc.text = item.ItemDesc;
            TextPrice.text = $"{item.ItemPrice}";
        }
        else
        {
            TextName.text = "";
            TextDesc.text = "Empty";
            TextPrice.text = "";
        }
    }

    public void Refresh()
    {
        Item Choice(Item[] items)
        {
            Item ret = null;
            int TotalWeight = 0;
            foreach (Item item in items)
            {
                TotalWeight += item.ItemRandomWeight;
                if (Random.value <= (float)item.ItemRandomWeight / TotalWeight)
                {
                    ret = item;
                }
            }
            return ret;
        }

        if (behaviour == ShopItemBehaviour.SellSkill)
        {
            item = Choice(shop.GetAllSkill());
        }
        else if (behaviour == ShopItemBehaviour.SellBuff)
        {
            item = Choice(shop.GetAllBuff());
        }
    }

    public void OnPointerClick(PointerEventData eventData)
    {
        if (behaviour == ShopItemBehaviour.SellSkill)
        {
            BuySkill();
        }
        else if (behaviour == ShopItemBehaviour.SellBuff)
        {
            BuyBuff();
        }
    }

    void BuySkill()
    {
        if (item is SkillItem && backpack.Pay(item.ItemPrice))
        {
            shop.ChoiceSkillPositon((SkillItem)item);
            item = null;
        }
    }

    void BuyBuff()
    {
        if (item is BuffItem && backpack.Pay(item.ItemPrice))
        {
            backpack.PushBuff((BuffItem)item);
            item = null;
            shop.Display();
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // getter

    Shop shop
    {
        get { return GameObject.Find("ShopCanvas").GetComponent<Shop>(); }
    }

    Backpack backpack
    {
        get { return GameObject.Find("Backpack")?.GetComponent<Backpack>(); }
    }

    Text TextName
    {
        get { return gameObject.transform.Find("ItemName").GetComponent<Text>(); }
    }

    Text TextDesc
    {
        get { return gameObject.transform.Find("ItemDescription").GetComponent<Text>(); }
    }

    Text TextPrice
    {
        get { return gameObject.transform.Find("ItemPrice").GetComponent<Text>(); }
    }
}

public enum ShopItemBehaviour
{
    DisplaySkillOne,
    DisplaySkillTwo,
    SellSkill,
    SellBuff,
}
