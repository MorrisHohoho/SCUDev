using UnityEngine;

[CreateAssetMenu(menuName = "Data/StateMachine/PlayerState/Die", fileName = "PlayerState_Die")]  //�ɴ���һ���ýű���Ӧ��Entity
public class PlayerState_Die : PlayerState
{

    [SerializeField] AudioClip dieClip;
    public override void Enter()
    {
        base.Enter();
        //����������ƶ�
        input.DisableGameplayInputs();
        //�������ٶȹ���
        player.SetVelocity(Vector2.zero);
        player.PlayAudio(dieClip);
    }

    public override void LogicUpdate()
    {

    }


}
