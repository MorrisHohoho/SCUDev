using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/Die", fileName = "PlayerState_Die")]  //可创建一个该脚本对应的Entity
public class PlayerState_Die : PlayerState
{

    [SerializeField] AudioClip dieClip;
    public override void Enter()
    {
        base.Enter();
        //死亡后禁用移动
        input.DisableGameplayInputs();
        //死亡后速度归零
        player.SetVelocity(Vector2.zero);
        player.PlayAudio(dieClip);
    }

    public override void LogicUpdate()
    {

    }


}
