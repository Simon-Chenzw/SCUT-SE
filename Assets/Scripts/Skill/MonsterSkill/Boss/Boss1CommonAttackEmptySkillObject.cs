using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss1CommonAttackEmptySkillObject : SkillObject
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
        GameObject SkillObject = Resources.Load<GameObject>("SkillRange/Boss1CommonAttackSkill");
        Vector3 position1 = new Vector3(bounds.center.x + bounds.size.x, bounds.min.y, 0);
        Vector3 position2 = new Vector3(bounds.center.x - bounds.size.x, bounds.min.y, 0);
        GameObject.Instantiate(SkillObject, position1, transform.rotation, transform);
        GameObject.Instantiate(SkillObject, position2, transform.rotation, transform);
    }

    public override void CalculateSkillDamage() { }
}
