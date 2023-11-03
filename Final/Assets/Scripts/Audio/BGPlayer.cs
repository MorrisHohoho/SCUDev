using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGPlayer : MonoBehaviour
{

    static BGPlayer s;

    private void Awake()
    {
        if (s == null)
            s = this;
        else if (s != this)
            Destroy(gameObject);

        DontDestroyOnLoad(gameObject);
    }
}
