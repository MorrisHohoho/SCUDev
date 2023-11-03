using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadingPlatform : MonoBehaviour
{
    [SerializeField] float resetTime = 3.0f;
    [SerializeField] float fadeTime = 2.0f;

    [SerializeField] Renderer platform2;
    [SerializeField] Renderer platform3;

    Collider2D collider;
    SpriteRenderer renderer;

    WaitForSeconds waitResetTime;
    WaitForSeconds waitFadeTime;

    bool playerOn = false;
    private void Awake()
    {
        collider = GetComponent<Collider2D>();
        renderer = GetComponent<SpriteRenderer>();
        waitResetTime = new WaitForSeconds(resetTime);
        waitFadeTime = new WaitForSeconds(fadeTime);
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.TryGetComponent<PlayerController>(component: out PlayerController player))
        {
            playerOn = true;
            player.enableCanDash();
            StartCoroutine(FadeCoroutine());
            StartCoroutine(ResetCoroutine());

        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.name == "Player")
        {

            playerOn = false;
        }
    }

    private void Reset()
    {
        collider.enabled = true;
        renderer.enabled = true;
        platform2.enabled = true;
        platform3.enabled = true;
    }

    IEnumerator ResetCoroutine()
    {
        yield return new WaitUntil(()=>renderer.isVisible == false);
        yield return waitResetTime;

        Reset();
    }

    IEnumerator FadeCoroutine()
    {
        yield return new WaitUntil(() => playerOn == true);
        yield return waitFadeTime;
        yield return new WaitUntil(() => playerOn == true);

        Fade();
    }

    void Fade()
    {
        collider.enabled = false;
        renderer.enabled = false;
        platform2.enabled = false;
        platform3.enabled = false;
    }

}
