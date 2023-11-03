using UnityEngine;
[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/CoyoteTime", fileName = "PlayerState_CoyoteTime")]
public class PlayerState_CoyoteTime : PlayerState
{

    [SerializeField] float runSpeed = 10f;
    [SerializeField]float coyoteTime = 0.1f;    //ÍÁÀÇÊ±¼ä
    public override void Enter()
    {
        base.Enter();
        player.unableGravity();
    }

    public override void Exit()
    {
        player.resetGravity();
    }
    public override void LogicUpdate()
    {
        if(input.Jump)
        {
            stateMachine.SwitchState(typeof(PlayerState_Jump));
        }
        if(StateDuration>coyoteTime || !input.Move)
        {
            stateMachine.SwitchState(typeof(PlayerState_Fall));
        }
    }

    public override void PhysicUpdate()
    {
        player.Move(runSpeed);
    }
}
