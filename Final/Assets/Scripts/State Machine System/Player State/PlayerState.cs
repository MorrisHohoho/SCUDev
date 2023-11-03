using UnityEngine;


//玩家状态实体
//ScriptableObject表明可以建立一个实体脚本文件
public class PlayerState : ScriptableObject, IState
{

    [SerializeField] string stateName;  //状态名
    [SerializeField,Range(0f,1f)] float transitionDuration = 0.1f;  //动画持续时间

    int stateHash;  //状态哈希，可以提高脚本效率
    protected Animator animator;    //动画器

    protected PlayerController player;  //控制器

    protected PlayerInput input;    //输入器

    protected PlayerStateMachine stateMachine;  //状态机

    float stateStartTime;   //状态开始时间
    protected bool IsAnimationFinished => StateDuration >= animator.GetCurrentAnimatorStateInfo(0).length;

    protected float StateDuration => Time.time - stateStartTime;    //状态持续时间


    //状态（string）转状态（Hash）
    void OnEnable()
    {
        stateHash = Animator.StringToHash(stateName);
    }


    //状态初始化，为状态绑定动画器，输入器，控制器，状态机
    public void Init(Animator animator,PlayerInput input,PlayerController player,PlayerStateMachine stateMachine)
    {
        this.animator = animator;
        this.input = input;
        this.player = player;
        this.stateMachine = stateMachine;
    }

    //播放动画
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
