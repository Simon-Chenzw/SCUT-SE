using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Skill : ScriptableObject
{
    public abstract string SkillName { get; }
    public abstract float GlobalCD { get; }
    public abstract float CD { get; }

    ////////////////////////////////////////////////////////////////////////////

    /// <summary>
    /// Create Skill Object
    /// </summary>
    /// <param name="bounds">
    /// bounds of the body
    /// </param>
    /// <param name="transform">
    /// Transform of the root component of character
    /// </param>
    public abstract void CreateSkill(Bounds bounds, Transform transform);

    /// <summary>
    /// check can this skill hit Enemy, only used for monster
    /// </summary>
    /// <param name="OurTransform">
    /// the transform of us
    /// </param>
    /// <param name="EnemyTransform">
    /// the transform of Enemy
    /// </param>
    /// <param name="bounds">
    /// our's bounds
    /// </param>
    public abstract bool CheckUseSkill(
        Bounds bounds,
        Transform OurTransform,
        Transform EnemyTransform
    );
}
