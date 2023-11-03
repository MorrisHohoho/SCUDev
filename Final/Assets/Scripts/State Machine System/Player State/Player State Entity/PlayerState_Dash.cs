using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/Dash", fileName = "PlayerState_Dash")]  //可创建一个该脚本对应的Entity
public class PlayerState_Dash : PlayerState
{
    [Header("Dash")]
    [SerializeField] 
    private float dashForce = 10f;   //冲刺速度
    [SerializeField]
    private float dashTime=1f;  //冲刺时间
    private bool isDash = false;

    Vector2 dir = Vector2.zero; //冲刺方向

    [SerializeField] AudioClip dashClip;


    public override void Enter()
    {
        base.Enter();
        player.resumeTime = Time.time + dashTime;
        isDash = true;
        player.canDash = false;
        dir.x = input.AxisX;
        dir.y = input.AxisY;

        player.PlayAudio(dashClip);
        player.dashParticle.Play();
    }

    public override void LogicUpdate()
    {
        if (input.Jump)
        {
            stateMachine.SwitchState(typeof(PlayerState_DashJump));
        }
        if(Time.time>player.resumeTime)
        {
            if (!player.IsGrounded)
            {
                stateMachine.SwitchState(typeof(PlayerState_Fall));
            }
            else
            stateMachine.SwitchState(typeof(PlayerState_Idle));
            isDash = false;
        }
        if (!player.getPlayerLife())
        {
            stateMachine.SwitchState(typeof(PlayerState_Die));
        }
    }

    public override void Exit()
    {
        base.Exit();
        player.resetGravity();
        player.dashParticle.Stop();
    }

    public override void PhysicUpdate()
    {
        if (isDash)
        {
            player.Dash(dashForce,dir.x,dir.y);
            ShadowPool.instance.GetFromPool();
        }
    }

}
