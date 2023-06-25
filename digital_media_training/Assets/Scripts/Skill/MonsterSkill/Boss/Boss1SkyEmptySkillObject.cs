using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss1SkyEmptySkillObject : SkillObject
{
    private int cnt = 0;
    private float PassedTime = 0.0f;

    public float TargetTime = 0.1f;

    public void Update()
    {
        PassedTime += Time.deltaTime;
        if (PassedTime >= TargetTime)
        {
            PassedTime = 0;
            Func();
            cnt++;
            if (cnt == 10)
            {
                Destroy(gameObject);
            }
        }
    }

    public void Func()
    {
        Bounds bounds = transform.parent.Find("LogicBody").GetComponent<BoxCollider2D>().bounds;
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/Boss1SkySkill");
        float posX = Random.Range(-23.5f, 23.5f);
        Vector3 position = new Vector3(posX, 13.5f, 0);
        GameObject.Instantiate(
            SkillObject,
            position,
            transform.rotation,
            transform.parent.transform
        );
    }

    public override void CalculateSkillDamage() { }
}
