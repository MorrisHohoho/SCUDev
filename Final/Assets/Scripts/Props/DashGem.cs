using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DashGem : MonoBehaviour
{
    [SerializeField] float resetTime =3.0f;
    Collider2D collider;
    SpriteRenderer renderer;

    WaitForSeconds waitResetTime;

    [SerializeField] AudioClip gemSFX;
    private void Awake()
    {
        collider = GetComponent<Collider2D>();
        renderer = GetComponent<SpriteRenderer>();
        waitResetTime = new WaitForSeconds(resetTime);
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.TryGetComponent<PlayerController>(component: out PlayerController player))
        {
            player.enableCanDash();
            SoundEffectsPlayer.AudioSource.PlayOneShot(gemSFX);

            collider.enabled = false;
            renderer.enabled = false;
            StartCoroutine(ResetCoroutine());

        }
    }

    private void Reset()
    {
        collider.enabled = true;
        renderer.enabled = true;
    }

    IEnumerator ResetCoroutine()
    {
        yield return waitResetTime;

        Reset();
    }
}
