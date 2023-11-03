using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/Fall", fileName = "PlayerState_Fall")]
public class PlayerState_Fall : PlayerState
{

    [SerializeField] AnimationCurve speedCurve;
    [SerializeField] float moveSpeed = 10f;

    public override void Enter()
    {
        base.Enter();
    }
    public override void LogicUpdate()
    {
        if(player.IsGrounded)
        {
            player.resetClimbTime = true;
            stateMachine.SwitchState(typeof(PlayerState_Idle));
        }
        if(player.WallDectector.IsGrounded)
        {
            if (input.AxisX != 0f || input.Climb)
            {
                if (player.resetClimbTime)
                setClimbTime();
                stateMachine.SwitchState(typeof(PlayerState_Climb));
            }
        }
        if(input.Dash&&player.canDash)
        {
            stateMachine.SwitchState(typeof(PlayerState_Dash));
        }
        if(input.Jump)
        {
            input.SetJumpInputBufferTimer();
        }
        if (!player.getPlayerLife())
        {
            stateMachine.SwitchState(typeof(PlayerState_Die));
        }
        if(player.getTrampolineJump())
        {
            stateMachine.SwitchState(typeof(PlayerState_Jump));
        }
    }

    public override void PhysicUpdate()
    {
        player.SetVelocityY(speedCurve.Evaluate(StateDuration));
        player.Move(player.WallDectector.IsGrounded ? 0f : moveSpeed);
    }

    void setClimbTime()
    {
        player.startClimbTime = Time.time;
        player.endClimbTime = player.startClimbTime + player.maxClimbTime;
        player.resetClimbTime = false;
    }

    public override void Exit()
    {
        base.Exit();
        player.resetGravity();
    }
}
