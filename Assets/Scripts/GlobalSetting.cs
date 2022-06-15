using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GlobalSetting : MonoBehaviour
{
    // 按键定义
    static public KeyCode LeftMoveKey = KeyCode.A;
    static public KeyCode RightMoveKey = KeyCode.D;
    static public KeyCode JumpKey = KeyCode.Space;
    static public KeyCode TeleportKey = KeyCode.E;
    static public KeyCode CommonAttackKey = KeyCode.J;
    static public KeyCode CommonManaAttackKey = KeyCode.K;
    static public KeyCode ExitKey = KeyCode.Escape;

    // 层级定义
    static public LayerMask PlatformLayerMask = 1 << 7;
    static public LayerMask WallLayerMask = 1 << 8;
    static public LayerMask TeleporterLayerMask = 1 << 9;
    static public LayerMask CharacterLayerMask = 1 << 11;
    static public LayerMask MonsterLayerMask = 1 << 12;

    // 怪物生成数量定义
    static public int[][] SpawnMonsterNumer = new int[24][]
    {
        new int[2] { 1, 0 },
        new int[2] { 1, 0 },
        new int[2] { 1, 0 },
        new int[2] { 1, 0 },
        new int[2] { 2, 1 },
        new int[2] { 2, 0 },
        new int[2] { 2, 0 },
        new int[2] { 2, 0 },
        new int[2] { 2, 0 },
        new int[2] { 2, 1 },
        new int[2] { 3, 0 },
        new int[2] { 3, 0 },
        new int[2] { 3, 0 },
        new int[2] { 3, 0 },
        new int[2] { 3, 1 },
        new int[2] { 3, 0 },
        new int[2] { 3, 0 },
        new int[2] { 3, 0 },
        new int[2] { 3, 0 },
        new int[2] { 2, 2 },
        new int[2] { 4, 0 },
        new int[2] { 4, 0 },
        new int[2] { 4, 0 },
        new int[2] { 4, 0 }
    };
}
