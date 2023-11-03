using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerGroundDetector : MonoBehaviour
{

    [SerializeField] float detectionRadius = 0.1f;  //�ж���ײ�ж�
    [SerializeField] LayerMask groundLayer;     //���β�

    Collider2D[] colliders = new Collider2D[1];     //��ײ��
  public bool IsGrounded
    {
        get
        {
            return Physics2D.OverlapCircleNonAlloc(transform.position, detectionRadius,colliders, groundLayer) != 0;
        }
    }


    //������ײ���Բ
    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(transform.position, detectionRadius);
    }
}
