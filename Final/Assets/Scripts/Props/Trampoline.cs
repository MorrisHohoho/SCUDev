using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Trampoline : MonoBehaviour
{
    Animator am;

    [SerializeField] float jumpForce = 20f; //  µØª…¡¶
    [SerializeField] AudioClip tramplolineClip;
    AudioSource audio;
    private void Awake()
    {
        am = GetComponent<Animator>();
        audio = GetComponent<AudioSource>();
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.TryGetComponent<PlayerController>(component: out PlayerController player))
        {
            am.SetTrigger("Jump");
            player.trampolineJump(jumpForce);
            player.setTrampolineJump(true);
            audio.clip = tramplolineClip;
            audio.Play();
        }
    }

}
