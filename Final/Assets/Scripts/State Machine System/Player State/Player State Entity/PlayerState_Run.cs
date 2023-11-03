using UnityEngine;

[CreateAssetMenu(menuName ="Data/StateMachine/PlayerState/Run",fileName ="PlayerState_Run")]
public class PlayerState_Run : PlayerState
{

    [SerializeField]float runSpeed = 10f;
    [SerializeField] AudioClip runClip;
    public override void Enter()
    {
        base.Enter();

        player.resetGravity();
        player.resetCanDash();
    }

    public override void LogicUpdate()
    {
        if (!input.Move)
        {
            stateMachine.SwitchState(typeof(PlayerState_Idle));
        }
        if (input.Jump)
        {
            stateMachine.SwitchState(typeof(PlayerState_Jump));
        }
        if (!player.IsGrounded)
        {
            stateMachine.SwitchState(typeof(PlayerState_CoyoteTime));
        }
        if (input.Dash&&player.canDash)
        {
            stateMachine.SwitchState(typeof(PlayerState_Dash));
        }
        if (!player.getPlayerLife())
        {
            stateMachine.SwitchState(typeof(PlayerState_Die));
        }
    }

    public override void PhysicUpdate()
    {
        player.Move(runSpeed);
        player.PlayAudio(runClip);
    }

    public override void Exit()
    {
        base.Exit();
        player.StopAudio();
    }
}
