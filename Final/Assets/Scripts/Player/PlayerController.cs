 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    PlayerInput input;  //������   

    Rigidbody2D rigidBody;  //�������

    SpriteRenderer sprite;  //��Ⱦ��

    AudioSource audio;      //��Ч����

    PlayerGroundDetector groundDetector;    //������

    [SerializeField] PlayerGroundDetector wallDetector; //�����м��ǽ����
    [SerializeField] PlayerGroundDetector wallDetectorTwo;    //�ŵ׵�ǽ����
 
    public PlayerGroundDetector WallDectector => wallDetector;  //����һ��ǽ������
    public PlayerGroundDetector FootWallDectector => wallDetectorTwo;

    [SerializeField]public Transform climbPos;

    public bool IsGrounded => groundDetector.IsGrounded;    //��������
    public bool IsFalling => rigidBody.velocity.y < 0f && !IsGrounded;//&& !WallDectector.IsGrounded; //��������

    public bool canDash =true;    //�Ƿ��ܹ����
    public float resumeTime; //��̻ظ���ԭ״̬����ʱ��

    [SerializeField]private float g = 10f; //Ĭ������

    public float startClimbTime;
    public float endClimbTime;
    public float maxClimbTime = 2f;  //�����ǽʱ��
    public bool resetClimbTime = true;
    public bool wallJumped = false;
    float wallJumpLerp = .5f;   //��ǽ����ֵ

    bool isAlive = true;    //��Ҵ��
    bool isTrampoline = false;    //������

    bool isPlatFormJump = false; //ƽ̨��
    float platformJumpDir;  //ƽ̨������


    [Space]
    [Header("Polish")]
    public ParticleSystem dashParticle;
    public ParticleSystem jumpParticle;
    public ParticleSystem wallJumpParticle;
    public ParticleSystem slideParticle;


    //��ȡʵ��
    void Awake()
    {
        groundDetector = GetComponentInChildren<PlayerGroundDetector>();
        input = GetComponent<PlayerInput>();
        rigidBody = GetComponent<Rigidbody2D>();
        sprite = GetComponent<SpriteRenderer>();
        audio = GetComponent<AudioSource>();
    }


    //����������
     void Start()
    {
        input.EnableGameplayInputs();
    }

    //�ƶ�
    public void Move(float speed)
    {
        //��ͼת��
        if (input.Move&&!input.Climb)
        {
            transform.localScale = new Vector3(input.AxisX, 1f, 1f);
        }
        //�����ƶ��ٶ�
        SetVelocityX(speed * input.AxisX);
    }

    //���
    public void Dash(float force,float x,float y)
    {
        if(y==0f)
            SetVelocity(new Vector2(force * getPlayerScale(), force * y));
        else
            SetVelocity(new Vector2(force * x, force*y ));

            rigidBody.gravityScale = 0f;
    }

    public float getVelocityX()
    {
        return rigidBody.velocity.x;
    }


    //��ȡY���ٶ�
    public float getVelocitY()
    {
        return rigidBody.velocity.y;
    }


    //�����ٶ�
    public void SetVelocity(Vector2 velocity)
    {
        rigidBody.velocity = velocity;
    }

    //����X���ٶ�
    public void SetVelocityX(float velocityX)
    {
        rigidBody.velocity = new Vector2(velocityX, rigidBody.velocity.y);
    }

    //����Y���ٶ�
    public void SetVelocityY(float velocityY)
    {
        rigidBody.velocity = new Vector2(rigidBody.velocity.x, velocityY);
    }

    //�����������ٶ�
    public void resetGravity()
    {
        rigidBody.gravityScale = g;
    }

    //���ݳ��ʱ�䣬���ó������
    public void resetCanDash()
    {
        if (Time.time > resumeTime) 
        canDash = true;
    }

    //�����������
    public void enableCanDash()
    {
        canDash = true;
    }

    //����泯����
    public float getPlayerScale()
    {
       return sprite.transform.localScale.x;
    }

    //�ر�����Ӱ��
    public void unableGravity()
    {
        rigidBody.gravityScale = 0f;
    }

    //��ǽ����ֵ�ٶ�
    public void JumpLerp(float moveSpeed)
    {
        rigidBody.velocity = Vector2.Lerp(rigidBody.velocity, (new Vector2(input.AxisX * moveSpeed, rigidBody.velocity.y)), wallJumpLerp * Time.deltaTime);
    }

    public void setPlayerLife(bool isAlive)
    {
        this.isAlive = isAlive;
    }

    public bool getPlayerLife()
    {
        return isAlive;
    }

    //������
    public void trampolineJump(float force)
    {
        SetVelocityY(1f);   //��һ�����ϵĳ��ٶȣ�������������������
        rigidBody.AddForce(new Vector2(0, force), ForceMode2D.Impulse); //����
        resetCanDash(); //�������������³��
    }

    public void setTrampolineJump(bool t)
    {
        this.isTrampoline = t;
    }
    public bool getTrampolineJump()
    {
        return isTrampoline;
    }

    public  Vector2  GetPlayerCoord()
    {
        return this.transform.position;
    }

    //�ƶ�ƽ̨������
    public void platformJump(float force)
    {
        if (Mathf.Abs(platformJumpDir)<10)
        rigidBody.AddForce(new Vector2(this.platformJumpDir*force, 0), ForceMode2D.Impulse);
        else
        {
            
            rigidBody.AddForce(new Vector2(0, (Mathf.Abs(this.platformJumpDir)-9) *1.1f ), ForceMode2D.Impulse);
        }
    }

    public void setPlayerformJump(bool t,float dir)
    {
        this.isPlatFormJump = t;
        this.platformJumpDir = dir;
    }

    public bool getPlayerformJump()
    {
        return this.isPlatFormJump;
    }

    //������Ч
    public void PlayAudio(AudioClip clip)
    {
        audio.clip = clip;
        if(audio.isPlaying==false)
        audio.Play();
    }

    //ֹͣ����
    public void StopAudio()
    {
        audio.Stop();
    }

}
