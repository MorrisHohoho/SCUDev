using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/Jump", fileName = "PlayerState_Jump")]
public class PlayerState_Jump : PlayerState
{

    [SerializeField] float jumpForce = 50f;
    [SerializeField] float moveSpeed = 10f;
    [SerializeField] AudioClip jumpClip;
    public override void Enter()
    {
        base.Enter();
        player.PlayAudio(jumpClip);
        player.jumpParticle.Play();
        WhichJump();
    }
    public override void LogicUpdate()
    {
     if(input.StopJump ||player.IsFalling)
        {
            player.wallJumped = false;
            stateMachine.SwitchState(typeof(PlayerState_Fall));
        }
     if(input.Dash&&player.canDash)
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
        //����ǽ����x���ٶ���Ϊ�㣬��ֹ���ǽ��
        player.Move(player.WallDectector.IsGrounded?0f:moveSpeed);

        if(player.getPlayerformJump())
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
        player.setPlayerformJump(false,0);
        base.Exit();
    }

    void WhichJump()
    {
        if(player.getTrampolineJump())
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
