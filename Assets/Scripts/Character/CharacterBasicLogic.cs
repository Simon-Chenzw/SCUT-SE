using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterBasicLogic : BasicLogic
{
    // NOTE: For testing
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.J))
        {
            TakeDamage(10);
        }
    }
}
