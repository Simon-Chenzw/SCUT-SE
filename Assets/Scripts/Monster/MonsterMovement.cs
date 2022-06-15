using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterMovement : MonoBehaviour
{
    [Header("Movement Settings")]
    public float MoveSpeed; // 移动速度

    public float DropProbability; // 下落概率

    private Collider2D MonsterCollider; // 怪物的碰撞组件
    private Rigidbody2D MonsterRigidbody; // 怪物的刚体组件
    private GameObject Character;

    void Start()
    {
        // 获取怪物的各种组件
        MonsterCollider = transform.GetComponent<BoxCollider2D>();
        MonsterRigidbody = transform.GetComponent<Rigidbody2D>();
        Character = GameObject.Find("Character");
    }

    ////////////////////////////////////////////////////////////////////////////
    // Detection functions

    [Header("Detect Settings")]
    public float DetectDistance; //左右移动探测距离
    public float DetectDepth; //往下探测距离
    public float DetectDepthOffset; //往下探测时偏移距离
    public float DetectCharacterWidth; // 探测附近玩家距离
    public float DetectCharacterHeight; // 探测附近玩家距离

    bool HasWallAtLeft()
    {
        RaycastHit2D Raycast = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center,
            Vector2.left,
            MonsterCollider.bounds.extents.x + DetectDistance,
            GlobalSetting.WallLayerMask
                | GlobalSetting.MonsterLayerMask
                | GlobalSetting.CharacterLayerMask
        );
        return Raycast.collider != null;
    }

    bool HasWallAtRight()
    {
        RaycastHit2D Raycast = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center,
            Vector2.right,
            MonsterCollider.bounds.extents.x + DetectDistance,
            GlobalSetting.WallLayerMask
                | GlobalSetting.MonsterLayerMask
                | GlobalSetting.CharacterLayerMask
        );
        return Raycast.collider != null;
    }

    bool HasPlatformAtLeft()
    {
        RaycastHit2D Raycast = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center
                + Vector2.left * (MonsterCollider.bounds.extents.x + DetectDepthOffset),
            Vector2.down,
            MonsterCollider.bounds.extents.y + DetectDepth,
            GlobalSetting.PlatformLayerMask
        );
        return Raycast.collider != null;
    }

    bool HasPlatformAtRight()
    {
        RaycastHit2D Raycast = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center
                + Vector2.right * (MonsterCollider.bounds.extents.x + DetectDepthOffset),
            Vector2.down,
            MonsterCollider.bounds.extents.y + DetectDepth,
            GlobalSetting.PlatformLayerMask
        );
        return Raycast.collider != null;
    }

    bool OnPlatform()
    {
        RaycastHit2D RaycastLeft = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center
                + Vector2.left * MonsterCollider.bounds.extents.x,
            Vector2.down,
            MonsterCollider.bounds.extents.y + DetectDepth,
            GlobalSetting.PlatformLayerMask
        );
        RaycastHit2D RaycastRight = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center
                + Vector2.right * MonsterCollider.bounds.extents.x,
            Vector2.down,
            MonsterCollider.bounds.extents.y + DetectDepth,
            GlobalSetting.PlatformLayerMask
        );
        return RaycastLeft.collider != null || RaycastRight.collider != null;
    }

    bool HasCharacterNear()
    {
        Collider2D collider = Physics2D.OverlapBox(
            new Vector2(
                MonsterCollider.bounds.center.x,
                MonsterCollider.bounds.center.y + DetectCharacterHeight / 2
            ),
            new Vector2(DetectCharacterWidth, DetectCharacterHeight),
            0,
            GlobalSetting.CharacterLayerMask
        );
        return collider != null;
    }

    bool HasCharacterLeft()
    {
        Collider2D collider = Physics2D.OverlapBox(
            new Vector2(
                MonsterCollider.bounds.center.x,
                MonsterCollider.bounds.center.y + DetectCharacterHeight / 2
            ),
            new Vector2(DetectCharacterWidth, DetectCharacterHeight),
            0,
            GlobalSetting.CharacterLayerMask
        );

        return collider != null
            && collider.transform.position.x <= MonsterCollider.transform.position.x;
    }

    bool HasCharacterRight()
    {
        Collider2D collider = Physics2D.OverlapBox(
            new Vector2(
                MonsterCollider.bounds.center.x,
                MonsterCollider.bounds.center.y - DetectCharacterHeight / 2
            ),
            new Vector2(DetectCharacterWidth, DetectCharacterHeight),
            0,
            GlobalSetting.CharacterLayerMask
        );
        return collider != null
            && collider.transform.position.x > MonsterCollider.transform.position.x;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Movement functions

    void Stand()
    {
        MonsterRigidbody.velocity = Vector2.zero;
    }

    void FacingLeft()
    {
        transform.Find("Render").transform.localScale = new Vector3(-1.0f, 1.0f, 1.0f);
    }

    void FacingRight()
    {
        transform.Find("Render").transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
    }

    void MoveLeft()
    {
        FacingLeft();
        if (!OnPlatform())
            return;
        if (!HasWallAtLeft())
        {
            MonsterRigidbody.velocity = Vector2.left * MoveSpeed;
        }
        else
        {
            Stand();
        }
    }

    void MoveRight()
    {
        FacingRight();
        if (!OnPlatform())
            return;
        if (!HasWallAtRight())
        {
            MonsterRigidbody.velocity = Vector2.right * MoveSpeed;
        }
        else
        {
            Stand();
        }
    }

    Vector2 GetFacing()
    {
        if (transform.Find("Render").transform.localScale.x == -1.0f)
            return Vector2.left;
        else
            return Vector2.right;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Decision functions

    //////////
    // Patrol

    private bool PatrolLeft = true;
    private bool PatrolAtCenter = true;
    private bool PatrolWillDrop = false;

    void PatrolMode()
    {
        bool platLeft = HasPlatformAtLeft();
        bool platRight = HasPlatformAtRight();
        if (platLeft && platRight)
        {
            if (!PatrolAtCenter)
            {
                PatrolWillDrop = Random.value < DropProbability;
            }
            PatrolAtCenter = true;
        }
        else if (OnPlatform())
        {
            PatrolAtCenter = false;
            if (!PatrolWillDrop)
            {
                PatrolLeft = platLeft;
            }
        }
        else
        {
            PatrolAtCenter = true;
            PatrolWillDrop = false;
            return;
        }

        if (PatrolLeft)
        {
            if (!HasWallAtLeft())
            {
                MoveLeft();
                PatrolLeft = true;
            }
            else
            {
                MoveRight();
                PatrolLeft = false;
            }
        }
        else
        {
            if (!HasWallAtRight())
            {
                MoveRight();
                PatrolLeft = false;
            }
            else
            {
                MoveLeft();
                PatrolLeft = true;
            }
        }
    }

    //////////
    // Attack


    [Header("Attack Settings")]
    public MonsterSkill[] Skills;

    void AttackWithSkill()
    {
        MonsterBasicLogic basiclogic = gameObject.GetComponent<MonsterBasicLogic>();
        if (basiclogic.InGlobalCD())
            return;
        foreach (Skill skill in Skills)
        {
            if (skill.CheckUseSkill(basiclogic.BodyBox.bounds, transform, Character.transform))
            {
                basiclogic.UseSkill(skill);
                return;
            }
        }
    }

    void AttackMode()
    {
        if (HasCharacterLeft())
        {
            MoveLeft();
            AttackWithSkill();
        }
        else if (HasCharacterRight())
        {
            MoveRight();
            AttackWithSkill();
        }
        else
        {
            PatrolMode();
        }
    }

    //////////
    // AI

    void AI()
    {
        if (HasCharacterNear())
        {
            AttackMode();
        }
        else
        {
            PatrolMode();
        }
    }

    private float RoundTime = 0.05f;
    private float RemainTime = 0;

    void FixedUpdate()
    {
        if ((RemainTime -= Time.deltaTime) <= 0)
        {
            AI();
            RemainTime = RoundTime;
        }
    }
}
