using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterMovement : MonoBehaviour
{
    [Header("Movement Settings")]
    public float MoveSpeed = 10.0f; // 移动速度
    public float JumpSpeed = 14.0f; // 跳跃速度
    public int MaxJumpChance = 2; // 最大跳跃段数

    [Header("Movement Status")]
    public bool IsJumping = false; // 是否正在跳跃
    public bool IsFalling = false; // 是否正在掉落
    public bool NeedTeleport = false; // 是否需要传送

    private Collider2D CharacterCollider; // 主角的碰撞组件
    private Rigidbody2D CharacterRigidbody; // 主角的刚体组件

    private int CurrentJumpChance; // 当前剩余跳跃段数

    void Start()
    {
        // 获取主角的各种组件
        CharacterCollider = transform.GetComponent<BoxCollider2D>();
        CharacterRigidbody = transform.GetComponent<Rigidbody2D>();

        CurrentJumpChance = MaxJumpChance; // 设置当前剩余跳跃段数
    }

    void Update()
    {
        // 判断是否进入掉落状态
        if (!IsFalling && CharacterRigidbody.velocity.y < 0)
        {
            // 若不是因为跳跃而进入掉落状态，则不允许跳跃
            if (!IsJumping)
            {
                CurrentJumpChance = 0;
            }
            IsJumping = false;
            IsFalling = true;
        }

        // 在空中时，将主角的碰撞体设为非触发器
        if (IsFalling && !CharacterCollider.IsTouchingLayers(GlobalSetting.PlatformLayerMask))
        {
            CharacterCollider.isTrigger = false;
        }

        // 判断是否落地
        if (
            IsFalling
            && CharacterRigidbody.velocity.y == 0
            && CharacterCollider.IsTouchingLayers(GlobalSetting.PlatformLayerMask)
        )
        {
            IsFalling = false;
            CurrentJumpChance = MaxJumpChance;
        }

        // 修改角色朝向
        if (Input.GetKey(GlobalSetting.RightMoveKey) && !Input.GetKey(GlobalSetting.LeftMoveKey))
        {
            transform.Find("RenderBody").localScale = new Vector3(1.0f, 1.0f, 1.0f);
            transform.Find("LogicBody").localScale = new Vector3(1.0f, 1.0f, 1.0f);
        }
        if (Input.GetKey(GlobalSetting.LeftMoveKey) && !Input.GetKey(GlobalSetting.RightMoveKey))
        {
            transform.Find("RenderBody").localScale = new Vector3(-1.0f, 1.0f, 1.0f);
            transform.Find("LogicBody").localScale = new Vector3(-1.0f, 1.0f, 1.0f);
        }

        // 根据轴输入移动（直接改变Transform）
        // transform.Translate(Input.GetAxis("Horizontal") * Time.deltaTime * MoveSpeed, 0.0f, 0.0f);

        // 根据轴输入移动（改变刚体速度）
        CharacterRigidbody.velocity = new Vector2(
            Input.GetAxis("Horizontal") * MoveSpeed,
            CharacterRigidbody.velocity.y
        );

        bool CanJump = true;

        // 若碰撞到墙，朝速度方向发射射线，射线碰到墙则停止该水平方向的移动，避免因为此时主角的碰撞体为触发器而穿墙
        if (CharacterCollider.IsTouchingLayers(GlobalSetting.WallLayerMask))
        {
            float InspectDistance = CharacterCollider.bounds.extents.x * 3;
            if (CharacterRigidbody.velocity.x > 0)
            {
                RaycastHit2D InspectRaycast1 = Physics2D.Raycast(
                    CharacterCollider.bounds.min,
                    Vector2.right,
                    InspectDistance,
                    GlobalSetting.WallLayerMask
                );
                RaycastHit2D InspectRaycast2 = Physics2D.Raycast(
                    CharacterCollider.bounds.max,
                    Vector2.right,
                    InspectDistance,
                    GlobalSetting.WallLayerMask
                );
                if (
                    InspectRaycast1.collider != null
                        && CharacterCollider.IsTouching(InspectRaycast1.collider)
                    || InspectRaycast2.collider != null
                        && CharacterCollider.IsTouching(InspectRaycast2.collider)
                )
                {
                    CharacterRigidbody.velocity = new Vector2(0.0f, CharacterRigidbody.velocity.y);
                }
            }
            else if (CharacterRigidbody.velocity.x < 0)
            {
                RaycastHit2D InspectRaycast1 = Physics2D.Raycast(
                    CharacterCollider.bounds.min,
                    Vector2.left,
                    InspectDistance,
                    GlobalSetting.WallLayerMask
                );
                RaycastHit2D InspectRaycast2 = Physics2D.Raycast(
                    CharacterCollider.bounds.max,
                    Vector2.left,
                    InspectDistance,
                    GlobalSetting.WallLayerMask
                );
                if (
                    InspectRaycast1.collider != null
                        && CharacterCollider.IsTouching(InspectRaycast1.collider)
                    || InspectRaycast2.collider != null
                        && CharacterCollider.IsTouching(InspectRaycast2.collider)
                )
                {
                    CharacterRigidbody.velocity = new Vector2(0.0f, CharacterRigidbody.velocity.y);
                }
            }

            if (CharacterRigidbody.velocity.y >= 0)
            {
                RaycastHit2D InspectRaycast1 = Physics2D.Raycast(
                    CharacterCollider.bounds.min,
                    Vector2.up,
                    InspectDistance,
                    GlobalSetting.WallLayerMask
                );
                RaycastHit2D InspectRaycast2 = Physics2D.Raycast(
                    CharacterCollider.bounds.max,
                    Vector2.up,
                    InspectDistance,
                    GlobalSetting.WallLayerMask
                );
                if (
                    InspectRaycast1.collider != null
                        && CharacterCollider.IsTouching(InspectRaycast1.collider)
                    || InspectRaycast2.collider != null
                        && CharacterCollider.IsTouching(InspectRaycast2.collider)
                )
                {
                    CharacterRigidbody.velocity = new Vector2(CharacterRigidbody.velocity.x, 0.0f);
                    CanJump = false;
                }
            }
        }

        // 跳跃按键输入
        if (Input.GetKeyDown(GlobalSetting.JumpKey) && CurrentJumpChance > 0 && CanJump)
        {
            CurrentJumpChance--;
            CharacterRigidbody.velocity = new Vector2(CharacterRigidbody.velocity.x, JumpSpeed);
            IsJumping = true;
            IsFalling = false;
            CharacterCollider.isTrigger = true; // 将主角的碰撞体设为触发器，使其能够穿越并跳上平台
        }

        // 传送按键输入
        if (
            Input.GetKeyDown(GlobalSetting.TeleportKey)
            && !IsJumping
            && !IsFalling
            && !NeedTeleport
            && CharacterCollider.IsTouchingLayers(GlobalSetting.TeleporterLayerMask)
        )
        {
            NeedTeleport = true; // 添加传送标记
        }
    }
}