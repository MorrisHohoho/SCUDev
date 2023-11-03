using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    [SerializeField] float minSpeed;    //初始移动速度
    [SerializeField] float a;   //加速度
    float speed;    //当前速度
    [SerializeField] float waitTime;
    [SerializeField] Transform[] movePos;
    [SerializeField] PlayerController player;

    [SerializeField] float dir;  //  速度方向,+1为右，-1为左

    private int i;
    private bool playerEnterPlatform = false;
    private bool playerOnPlatform = false;
    private bool moveBack = false;
    private bool canPlatformJump = false;
    private float platformJumpTime = 0.2f; //平台跳时间
    private bool corotinue = false; //协程开启

    public AudioClip StartClip;
    public AudioClip ImpactClip;
    public AudioClip ReturnClip;
    public AudioClip ReImpactClip;

    public AudioSource audio;

    bool isAudioPlay = false;
    bool isAudioReturn = false;

    private void Start()
    {
        audio = this.GetComponent<AudioSource>();
        i = 1;  //i=1代表endPos
        speed = minSpeed;
    }

    private void FixedUpdate()
    {
        if (playerEnterPlatform)
        {
            //向endpos移动
            transform.position = Vector2.MoveTowards(transform.position, movePos[i].position, speed * Time.deltaTime);

            //如果不是往回移动，则平台加速
            if (!moveBack)
            {
                speed += a;
                if(!isAudioPlay)
                {
                    PlayAudio(StartClip);
                    isAudioPlay = true;
                }
            }
            else
            {
                if (!isAudioReturn)
                {
                    PlayAudio(ReturnClip);
                    isAudioReturn = true;
                }
            }

            if (Vector2.Distance(transform.position, movePos[i].position) < 0.1f)
            {

                //如果玩家还在平台上，开启协程
                if (playerOnPlatform && !corotinue)
                {
                    SetTimer();
                    corotinue = true;
                }
                

                if (waitTime < 0.0f)
                {
                    //回到了startPos
                    if (i == 0)
                    {
                        i = 1;
                        speed = minSpeed;
                        moveBack = false;
                        corotinue = false;
                        playerEnterPlatform = false;
                        isAudioPlay = false;
                        isAudioReturn = false;
                    }
                    else
                    {
                        i = 0;
                        moveBack = true;
                        corotinue = false;
                        isAudioPlay = false;
                    }

                    waitTime = 0.5f;
                }

                else
                {
                    if (moveBack == true)
                        PlayAudio(ImpactClip);
                    else
                        PlayAudio(ReImpactClip);
                    waitTime -= Time.deltaTime;
                }
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.name=="Player")
        {
            collision.gameObject.transform.SetParent(transform);
            playerEnterPlatform=true;
            playerOnPlatform = true;
        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if(collision.gameObject.name=="Player")
        {
            collision.gameObject.transform.SetParent(null);
            playerOnPlatform = false;
            player.setPlayerformJump(canPlatformJump,dir);
        }
    }
    public void SetTimer()
    {
        StopCoroutine(nameof(JumpInputBufferCoroutine));
        StartCoroutine(nameof(JumpInputBufferCoroutine));
    }
    IEnumerator JumpInputBufferCoroutine()
    {
        canPlatformJump = true;

        yield return new WaitForSeconds(platformJumpTime);

        canPlatformJump = false;

    }

    public void PlayAudio(AudioClip clip)
    {
        audio.clip = clip;
        if(audio.isPlaying==false)
        {
            audio.Play();
        }
    }
}
