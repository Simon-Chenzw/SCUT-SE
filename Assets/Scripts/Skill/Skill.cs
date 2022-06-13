using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Skill : ScriptableObject
{
    public abstract string SkillName { get; }
    public abstract float GlobalCD { get; }
    public abstract float CD { get; }
    public abstract float MPcost { get; }

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
}
