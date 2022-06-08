using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterMovement : MonoBehaviour
{
    [Header("Movement Settings")]
    public float MoveSpeed; // 移动速度

    public float DropProbability; // 下落概率

    [Header("Layer Settings")]
    public LayerMask PlatformLayerMask; // 平台层
    public LayerMask WallLayerMask; // 墙壁层
    public LayerMask MonsterMask; // 怪物层
    public LayerMask CharacterMask; // 人物层

    private Collider2D MonsterCollider; // 怪物的碰撞组件
    private Rigidbody2D MonsterRigidbody; // 怪物的刚体组件

    void Start()
    {
        // 获取怪物的各种组件
        MonsterCollider = transform.GetComponent<BoxCollider2D>();
        MonsterRigidbody = transform.GetComponent<Rigidbody2D>();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Detection functions

    [Header("Detect Settings")]
    public float DetectDistance; //左右移动探测距离
    public float DetectDepth; //往下探测距离
    public float DetectDepthOffset; //往下探测时偏移距离

    bool HasWallAtLeft()
    {
        RaycastHit2D Raycast = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center,
            Vector2.left,
            MonsterCollider.bounds.extents.x + DetectDistance,
            WallLayerMask | MonsterMask | CharacterMask
        );
        return Raycast.collider != null;
    }

    bool HasWallAtRight()
    {
        RaycastHit2D Raycast = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center,
            Vector2.right,
            MonsterCollider.bounds.extents.x + DetectDistance,
            WallLayerMask | MonsterMask | CharacterMask
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
            PlatformLayerMask
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
            PlatformLayerMask
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
            PlatformLayerMask
        );
        RaycastHit2D RaycastRight = Physics2D.Raycast(
            (Vector2)MonsterCollider.bounds.center
                + Vector2.right * MonsterCollider.bounds.extents.x,
            Vector2.down,
            MonsterCollider.bounds.extents.y + DetectDepth,
            PlatformLayerMask
        );
        return RaycastLeft.collider != null || RaycastRight.collider != null;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Movement functions

    void Stand()
    {
        MonsterRigidbody.velocity = Vector2.zero * MoveSpeed;
    }

    void MoveLeft()
    {
        transform.Find("Render").transform.localScale = new Vector3(-1.0f, 1.0f, 1.0f);
        MonsterRigidbody.velocity = Vector2.left * MoveSpeed;
    }

    void MoveRight()
    {
        transform.Find("Render").transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
        MonsterRigidbody.velocity = Vector2.right * MoveSpeed;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Decision functions

    //////////
    // WalkAround

    private bool WalkAroundLeft = true;
    private bool WalkAroundAtCenter = true;
    private bool WalkAroundWillDrop = false;

    void WalkAround()
    {
        bool platLeft = HasPlatformAtLeft();
        bool platRight = HasPlatformAtRight();
        if (platLeft && platRight)
        {
            if (!WalkAroundAtCenter)
            {
                WalkAroundWillDrop = Random.value < DropProbability;
            }
            WalkAroundAtCenter = true;
        }
        else if (OnPlatform())
        {
            WalkAroundAtCenter = false;
            if (!WalkAroundWillDrop)
            {
                WalkAroundLeft = platLeft;
            }
        }
        else
        {
            WalkAroundAtCenter = true;
            WalkAroundWillDrop = false;
            return;
        }

        if (WalkAroundLeft)
        {
            if (!HasWallAtLeft())
            {
                MoveLeft();
                WalkAroundLeft = true;
            }
            else
            {
                MoveRight();
                WalkAroundLeft = false;
            }
        }
        else
        {
            if (!HasWallAtRight())
            {
                MoveRight();
                WalkAroundLeft = false;
            }
            else
            {
                MoveLeft();
                WalkAroundLeft = true;
            }
        }
    }

    //////////
    // AI

    void AI()
    {
        WalkAround();
    }

    private float RoundTime = 0.05f;
    private float RemainTime = 0;

    // private bool _OnPlatform;
    // private bool _LeftWall;
    // private bool _RightWall;
    // private bool _LeftPlatform;
    // private bool _RightPlatform;

    void FixedUpdate()
    {
        // _OnPlatform = OnPlatform();
        // _LeftWall = HasWallAtLeft();
        // _RightWall = HasWallAtRight();
        // _LeftPlatform = HasPlatformAtLeft();
        // _RightPlatform = HasPlatformAtRight();

        if (RemainTime <= 0)
        {
            AI();
            RemainTime = RoundTime;
        }
        else
        {
            RemainTime -= Time.deltaTime;
        }
    }
}
