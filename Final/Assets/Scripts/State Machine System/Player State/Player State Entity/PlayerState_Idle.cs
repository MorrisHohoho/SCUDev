using UnityEngine;

[CreateAssetMenu(menuName ="Data/StateMachine/PlayerState/Idle",fileName ="PlayerState_Idle")]  //可创建一个该脚本对应的Entity
public class PlayerState_Idle : PlayerState
{

    //进入Idle状态
    public override void Enter()
    {
        base.Enter();

        player.resetGravity();
        player.SetVelocityX(0f);
        player.resetCanDash();
    }

    //Idle逻辑
    public override void LogicUpdate()
    {
        if(input.Move)
        {
            stateMachine.SwitchState(typeof(PlayerState_Run));
        }
        if (input.HasJumpInputBuffer||input.Jump)
        {
            stateMachine.SwitchState(typeof(PlayerState_Jump));
        }

        if (!player.IsGrounded)
        {
            stateMachine.SwitchState(typeof(PlayerState_Fall));
        }
        if(input.Dash)
        {
            stateMachine.SwitchState(typeof(PlayerState_Dash));
        }
        if (!player.getPlayerLife())
        {
            stateMachine.SwitchState(typeof(PlayerState_Die));
        }

    }

   
}
