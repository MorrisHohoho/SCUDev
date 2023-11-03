using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStateMachine : StateMachine
{

    [SerializeField]PlayerState[] states;   //状态数组
    Animator animator;  //动画器
    PlayerInput input;  //输入器
    PlayerController player;    //控制器

    //初始化
    private void Awake()
    {
        animator = GetComponent<Animator>();    //获取动画器

        stateTable = new Dictionary<System.Type, IState>(states.Length);    //状态字典

        input = GetComponent<PlayerInput>();    //获取输入器

        player = GetComponent<PlayerController>();  //获取控制器

        //状态机初始化
        foreach(PlayerState state in states)
        {
            state.Init(animator,input,player,this);
            stateTable.Add(state.GetType(), state);
        }
    }

    //初始化状态为Idle
    private void Start()
    {
        SwitchOn(stateTable[typeof(PlayerState_Idle)]);
    }
}
