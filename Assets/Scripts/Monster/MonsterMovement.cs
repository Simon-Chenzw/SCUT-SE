using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterMovement : MonoBehaviour
{
    [Header("Movement Settings")]
    public float MoveSpeed = 8.0f; // 移动速度
    public float JumpSpeed = 0.0f; // 跳跃速度
    public int MaxJumpChance = 0; // 最大跳跃段数

    [Header("Movement Status")]
    public bool IsJumping = false; // 是否正在跳跃
    public bool IsFalling = false; // 是否正在掉落

    [Header("Command Settings")]
    public float CommandCD = 1.0f; // AI指令间隔
    public float CommandCDFloat = 0.3f; // AI指令间隔浮动区间

    [Header("Layer Settings")]
    public LayerMask PlatformLayerMask; // 平台层
    public LayerMask WallLayerMask; // 墙壁层

    private Collider2D MonsterCollider; // 怪物的碰撞组件
    private Rigidbody2D MonsterRigidbody; // 怪物的刚体组件

    private int CurrentJumpChance; // 当前剩余跳跃段数
    private float CommandCountDown; // AI指令可用倒计时

    void Start()
    {
        // 获取怪物的各种组件
        MonsterCollider = transform.GetComponent<BoxCollider2D>();
        MonsterRigidbody = transform.GetComponent<Rigidbody2D>();

        CurrentJumpChance = MaxJumpChance;
        CommandCountDown = CommandCD;
    }

    void Update()
    {
        // 判断是否进入掉落状态
        if (!IsFalling && MonsterRigidbody.velocity.y < 0)
        {
            IsJumping = false;
            IsFalling = true;
            MonsterCollider.isTrigger = false;
        }

        // 判断是否落地
        if (
            IsFalling
            && MonsterRigidbody.velocity.y == 0
            && MonsterRigidbody.IsTouchingLayers(PlatformLayerMask)
        )
        {
            IsFalling = false;
            CurrentJumpChance = MaxJumpChance;
        }

        // 修改怪物朝向
        if (MonsterRigidbody.velocity.x > 0)
        {
            transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
        }
        else if (MonsterRigidbody.velocity.x < 0)
        {
            transform.localScale = new Vector3(-1.0f, 1.0f, 1.0f);
        }

        // 撞墙处理
        if (MonsterCollider.IsTouchingLayers(WallLayerMask))
        {
            float InspectDistance = MonsterCollider.bounds.extents.x * 3;
            if (MonsterRigidbody.velocity.x > 0)
            {
                RaycastHit2D InspectRaycast1 = Physics2D.Raycast(
                    MonsterCollider.bounds.min,
                    Vector2.right,
                    InspectDistance,
                    WallLayerMask
                );
                RaycastHit2D InspectRaycast2 = Physics2D.Raycast(
                    MonsterCollider.bounds.max,
                    Vector2.right,
                    InspectDistance,
                    WallLayerMask
                );
                if (
                    InspectRaycast1.collider != null
                        && MonsterCollider.IsTouching(InspectRaycast1.collider)
                    || InspectRaycast2.collider != null
                        && MonsterCollider.IsTouching(InspectRaycast2.collider)
                )
                {
                    MonsterRigidbody.velocity = new Vector2(0.0f, MonsterRigidbody.velocity.y);
                }
            }
            else if (MonsterRigidbody.velocity.x < 0)
            {
                RaycastHit2D InspectRaycast1 = Physics2D.Raycast(
                    MonsterCollider.bounds.min,
                    Vector2.left,
                    InspectDistance,
                    WallLayerMask
                );
                RaycastHit2D InspectRaycast2 = Physics2D.Raycast(
                    MonsterCollider.bounds.max,
                    Vector2.left,
                    InspectDistance,
                    WallLayerMask
                );
                if (
                    InspectRaycast1.collider != null
                        && MonsterCollider.IsTouching(InspectRaycast1.collider)
                    || InspectRaycast2.collider != null
                        && MonsterCollider.IsTouching(InspectRaycast2.collider)
                )
                {
                    MonsterRigidbody.velocity = new Vector2(0.0f, MonsterRigidbody.velocity.y);
                }
            }
        }

        CommandCountDown -= Time.deltaTime;
        if (CommandCountDown < 0)
        {
            MovementControl(); // 怪物的移动控制（AI）
        }
    }

    private void MovementControl()
    {
        int Command = Random.Range(0, 2);
        if (Command == 0) // 左移
        {
            MonsterRigidbody.velocity = new Vector2(-MoveSpeed, MonsterRigidbody.velocity.y);
        }
        else if (Command == 1) // 右移
        {
            MonsterRigidbody.velocity = new Vector2(MoveSpeed, MonsterRigidbody.velocity.y);
        }

        CommandCountDown = CommandCD + Random.Range(-CommandCDFloat, CommandCDFloat); // 重置倒计时
    }
}
