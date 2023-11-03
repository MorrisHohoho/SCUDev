 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    PlayerInput input;  //输入器   

    Rigidbody2D rigidBody;  //人物刚体

    SpriteRenderer sprite;  //渲染器

    AudioSource audio;      //音效播放

    PlayerGroundDetector groundDetector;    //地面检测

    [SerializeField] PlayerGroundDetector wallDetector; //身体中间的墙体检测
    [SerializeField] PlayerGroundDetector wallDetectorTwo;    //脚底的墙体检测
 
    public PlayerGroundDetector WallDectector => wallDetector;  //创建一个墙体检测器
    public PlayerGroundDetector FootWallDectector => wallDetectorTwo;

    [SerializeField]public Transform climbPos;

    public bool IsGrounded => groundDetector.IsGrounded;    //地面检测标记
    public bool IsFalling => rigidBody.velocity.y < 0f && !IsGrounded;//&& !WallDectector.IsGrounded; //掉落检测标记

    public bool canDash =true;    //是否能够冲刺
    public float resumeTime; //冲刺回复成原状态所需时间

    [SerializeField]private float g = 10f; //默认重力

    public float startClimbTime;
    public float endClimbTime;
    public float maxClimbTime = 2f;  //最大爬墙时间
    public bool resetClimbTime = true;
    public bool wallJumped = false;
    float wallJumpLerp = .5f;   //蹬墙跳插值

    bool isAlive = true;    //玩家存活
    bool isTrampoline = false;    //弹簧跳

    bool isPlatFormJump = false; //平台跳
    float platformJumpDir;  //平台跳方向


    [Space]
    [Header("Polish")]
    public ParticleSystem dashParticle;
    public ParticleSystem jumpParticle;
    public ParticleSystem wallJumpParticle;
    public ParticleSystem slideParticle;


    //获取实体
    void Awake()
    {
        groundDetector = GetComponentInChildren<PlayerGroundDetector>();
        input = GetComponent<PlayerInput>();
        rigidBody = GetComponent<Rigidbody2D>();
        sprite = GetComponent<SpriteRenderer>();
        audio = GetComponent<AudioSource>();
    }


    //启动输入器
     void Start()
    {
        input.EnableGameplayInputs();
    }

    //移动
    public void Move(float speed)
    {
        //贴图转向
        if (input.Move&&!input.Climb)
        {
            transform.localScale = new Vector3(input.AxisX, 1f, 1f);
        }
        //设置移动速度
        SetVelocityX(speed * input.AxisX);
    }

    //冲刺
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


    //获取Y轴速度
    public float getVelocitY()
    {
        return rigidBody.velocity.y;
    }


    //设置速度
    public void SetVelocity(Vector2 velocity)
    {
        rigidBody.velocity = velocity;
    }

    //设置X轴速度
    public void SetVelocityX(float velocityX)
    {
        rigidBody.velocity = new Vector2(velocityX, rigidBody.velocity.y);
    }

    //设置Y轴速度
    public void SetVelocityY(float velocityY)
    {
        rigidBody.velocity = new Vector2(rigidBody.velocity.x, velocityY);
    }

    //重置重力加速度
    public void resetGravity()
    {
        rigidBody.gravityScale = g;
    }

    //根据冲刺时间，重置冲刺能力
    public void resetCanDash()
    {
        if (Time.time > resumeTime) 
        canDash = true;
    }

    //启动冲刺能力
    public void enableCanDash()
    {
        canDash = true;
    }

    //获得面朝方向
    public float getPlayerScale()
    {
       return sprite.transform.localScale.x;
    }

    //关闭重力影响
    public void unableGravity()
    {
        rigidBody.gravityScale = 0f;
    }

    //蹬墙跳插值速度
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

    //跳板跳
    public void trampolineJump(float force)
    {
        SetVelocityY(1f);   //给一个向上的初速度，否则人物会黏在跳板上
        rigidBody.AddForce(new Vector2(0, force), ForceMode2D.Impulse); //加速
        resetCanDash(); //弹起来可以重新冲刺
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

    //移动平台惯性跳
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

    //播放音效
    public void PlayAudio(AudioClip clip)
    {
        audio.clip = clip;
        if(audio.isPlaying==false)
        audio.Play();
    }

    //停止播放
    public void StopAudio()
    {
        audio.Stop();
    }

}
