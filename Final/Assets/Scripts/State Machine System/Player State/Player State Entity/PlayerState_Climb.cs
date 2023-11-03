using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/Climb", fileName = "PlayerState_Climb")]
public class PlayerState_Climb : PlayerState
{

    [SerializeField] float moveSpeed = 5f; //爬墙速度
    [SerializeField] AnimationCurve speedCurve; //沿墙体下滑速度
 
    public override void Enter()
    {
        base.Enter();
        player.startClimbTime = Time.time;
        player.endClimbTime = player.startClimbTime + player.maxClimbTime;
    }
    public override void LogicUpdate()
    {
        if (player.IsGrounded)
        {
            stateMachine.SwitchState(typeof(PlayerState_Idle));
        }
        if(input.StopClimb)
        {
            stateMachine.SwitchState(typeof(PlayerState_Fall));
        }

        if(!player.WallDectector.IsGrounded)
        {
            if(!player.FootWallDectector.IsGrounded)
                stateMachine.SwitchState(typeof(PlayerState_Fall));
            if (player.FootWallDectector.IsGrounded && input.AxisY > 0f)
            {
                player.transform.SetPositionAndRotation(player.climbPos.position, player.transform.rotation);
                if (!player.FootWallDectector.IsGrounded)
                    stateMachine.SwitchState(typeof(PlayerState_Idle));
            }
            
        }
        if(input.Jump)
        {
            player.wallJumped = true;
            player.wallJumpParticle.Play();
            stateMachine.SwitchState(typeof(PlayerState_Jump));
        }
        if(!player.getPlayerLife())
        {
            stateMachine.SwitchState(typeof(PlayerState_Die));
        }
    }

    public override void PhysicUpdate()
    {
        player.unableGravity();
        if (!input.Climb||player.startClimbTime>player.endClimbTime)
        {
            player.SetVelocityY(speedCurve.Evaluate(StateDuration));
            player.slideParticle.Play();

        }
        else
        {
            player.SetVelocityY(moveSpeed*input.AxisY);
            //上下爬的时候才开始计时
           if(input.AxisY!=0f)
            {
                player.startClimbTime += Time.deltaTime;
            }
        }
        player.Move(player.WallDectector.IsGrounded ? 0f : moveSpeed);
    }

    public override void Exit()
    {
        base.Exit();
        player.resetGravity();
    }
}
