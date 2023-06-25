using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Backpack : MonoBehaviour
{
    [Header("Settings")]
    public SkillItem[] Skills;

    [Header("Status")]
    private int gold = 0;

    [SerializeField] // Note: Public for testing
    private List<BuffItem> Buffs = new List<BuffItem>();

    void Start()
    {
        Display();
        DontDestroyOnLoad(gameObject);
    }

    public int GetGold()
    {
        return gold;
    }

    public void Get(int got)
    {
        gold += got;
        Display();
    }

    public bool Pay(int amounts)
    {
        if (gold >= amounts)
        {
            gold -= amounts;
            Display();
            return true;
        }
        else
        {
            return false;
        }
    }

    public void Display()
    {
        GameObject.Find("GoldNumber").GetComponent<Text>().text = gold.ToString();
    }

    public void SwapSkill()
    {
        SkillItem tmp = Skills[0];
        Skills[0] = Skills[1];
        Skills[1] = tmp;
    }

    public void ReplaceSkill(SkillItem item, int index)
    {
        if (0 <= index | index < Skills.Length)
        {
            Skills[index] = item;
        }
    }

    public void PushBuff(BuffItem item)
    {
        Buffs.Add(item);
    }

    public void SetBuff(CharacterBasicLogic logic)
    {
        int hp_add = 0;
        float hp_mul = 0.0f;
        float atk_add = 0.0f;
        float atk_mul = 0.0f;
        float def_add = 0.0f;
        float def_mul = 0.0f;

        foreach (BuffItem item in Buffs)
        {
            hp_add += item.HpAdd;
            hp_mul += item.HpMul;
            atk_add += item.AtkAdd;
            atk_mul += item.AtkMul;
            def_add += item.DefAdd;
            def_mul += item.DefMul;
        }

        logic.SetMaxHP(Mathf.CeilToInt((logic.BaseHP + hp_add) * (1 + hp_mul)));
        logic.SetATK((logic.BaseATK + atk_add) * (1 + atk_mul));
        logic.SetDEF((logic.BaseDEF + def_add) * (1 + def_mul));
    }

    ////////////////////////////////////////////////////////////////////////////
    // getter

    public CharacterSkill SkillOne
    {
        get
        {
            if (Skills == null || Skills.Length < 1)
                return null;
            else
                return Skills[0].skill;
        }
    }

    public SkillItem SkillItemOne
    {
        get
        {
            if (Skills == null || Skills.Length < 1)
                return null;
            else
                return Skills[0];
        }
    }

    public CharacterSkill SkillTwo
    {
        get
        {
            if (Skills == null || Skills.Length < 2)
                return null;
            else
                return Skills[1].skill;
        }
    }

    public SkillItem SkillItemTwo
    {
        get
        {
            if (Skills == null || Skills.Length < 2)
                return null;
            else
                return Skills[1];
        }
    }

    public float Vulnerable
    {
        get
        {
            float Vulnerable = 0.0f;
            foreach (BuffItem item in Buffs)
            {
                Vulnerable += item.Vulnerable;
            }
            return Vulnerable;
        }
    }
}
