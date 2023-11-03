using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowPool : MonoBehaviour
{
    //ʹ�õ���ģʽ
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

            //���ض����,�ȴ�ʹ��
            ReturnPool(newShadow);
        }
    }


    //���ض���
    public void ReturnPool(GameObject gameObject)
    {
        gameObject.SetActive(false);

        availabeObjects.Enqueue(gameObject);
    }

    //��ö���
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
