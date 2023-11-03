using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/DashJump", fileName = "PlayerState_DashJump")]
public class PlayerState_DashJump : PlayerState
{
    [SerializeField] float jumpForce = 50f;
    [SerializeField] float moveSpeed = 30f;
    public override void Enter()
    {
        base.Enter();
        WhichJump();
    }
    public override void LogicUpdate()
    {
        if (input.StopJump || player.IsFalling)
        {
            player.wallJumped = false;
            stateMachine.SwitchState(typeof(PlayerState_Fall));
        }
        if (input.Dash && player.canDash)
        {
            player.wallJumped = false;
            stateMachine.SwitchState(typeof(PlayerState_Dash));
        }
        if (!player.getPlayerLife())
        {
            stateMachine.SwitchState(typeof(PlayerState_Die));
        }
    }

    public override void PhysicUpdate()
    {
        //碰倒墙，把x轴速度设为零，防止黏在墙上
        player.Move(player.WallDectector.IsGrounded ? 0f : moveSpeed);

        if (player.getPlayerformJump())
        {
            player.platformJump(30f);
        }
        if (player.wallJumped)
        {
            player.JumpLerp(moveSpeed);
        }
    }

    public override void Exit()
    {
        player.setPlayerformJump(false, 0);
        base.Exit();
    }

    void WhichJump()
    {
        if (player.getTrampolineJump())
        {
            player.setTrampolineJump(false);
            player.resetGravity();
        }
        else
        {
            player.resetGravity();
            player.SetVelocityY(jumpForce);

            input.HasJumpInputBuffer = false;
        }
    }


}
