using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerGroundDetector : MonoBehaviour
{

    [SerializeField] float detectionRadius = 0.1f;  //ÅÐ¶ÏÅö×²ÅÐ¶¨
    [SerializeField] LayerMask groundLayer;     //µØÐÎ²ã

    Collider2D[] colliders = new Collider2D[1];     //Åö×²Ìå
  public bool IsGrounded
    {
        get
        {
            return Physics2D.OverlapCircleNonAlloc(transform.position, detectionRadius,colliders, groundLayer) != 0;
        }
    }


    //»æÖÆÅö×²¼ì²âÔ²
    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(transform.position, detectionRadius);
    }
}
