using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowPool : MonoBehaviour
{
    //使用单例模式
    public static ShadowPool instance;

    public GameObject shadowPrefab;

    [SerializeField] int shadowCount;

    private Queue<GameObject> availabeObjects = new Queue<GameObject>();

    private void Awake()
    {
        instance = this;

        FillPool();
    }

    public void FillPool()
    {
        for (int i = 0; i < shadowCount; i++)
        {
            var newShadow = Instantiate(shadowPrefab);
            newShadow.transform.SetParent(transform);

            //返回对象池,等待使用
            ReturnPool(newShadow);
        }
    }


    //返回对象
    public void ReturnPool(GameObject gameObject)
    {
        gameObject.SetActive(false);

        availabeObjects.Enqueue(gameObject);
    }

    //获得对象
    public GameObject GetFromPool()
    {
        if (availabeObjects.Count == 0)
        {
            FillPool();
        }
        var outShadow = availabeObjects.Dequeue();

        outShadow.SetActive(true);

        return outShadow;
    }
}
