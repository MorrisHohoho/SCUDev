using UnityEngine;


//���״̬ʵ��
//ScriptableObject�������Խ���һ��ʵ��ű��ļ�
public class PlayerState : ScriptableObject, IState
{

    [SerializeField] string stateName;  //״̬��
    [SerializeField,Range(0f,1f)] float transitionDuration = 0.1f;  //��������ʱ��

    int stateHash;  //״̬��ϣ��������߽ű�Ч��
    protected Animator animator;    //������

    protected PlayerController player;  //������

    protected PlayerInput input;    //������

    protected PlayerStateMachine stateMachine;  //״̬��

    float stateStartTime;   //״̬��ʼʱ��
    protected bool IsAnimationFinished => StateDuration >= animator.GetCurrentAnimatorStateInfo(0).length;

    protected float StateDuration => Time.time - stateStartTime;    //״̬����ʱ��


    //״̬��string��ת״̬��Hash��
    void OnEnable()
    {
        stateHash = Animator.StringToHash(stateName);
    }


    //״̬��ʼ����Ϊ״̬�󶨶�����������������������״̬��
    public void Init(Animator animator,PlayerInput input,PlayerController player,PlayerStateMachine stateMachine)
    {
        this.animator = animator;
        this.input = input;
        this.player = player;
        this.stateMachine = stateMachine;
    }

    //���Ŷ���
    public virtual void Enter()
    {
        animator.CrossFade(stateHash, transitionDuration);
        stateStartTime = Time.time;
    }

    public virtual void Exit()
    {
      
    }

    public virtual void LogicUpdate()
    {
     
    }

    public virtual void PhysicUpdate()
    {
     
    }
}
