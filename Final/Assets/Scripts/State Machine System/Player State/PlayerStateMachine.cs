using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStateMachine : StateMachine
{

    [SerializeField]PlayerState[] states;   //״̬����
    Animator animator;  //������
    PlayerInput input;  //������
    PlayerController player;    //������

    //��ʼ��
    private void Awake()
    {
        animator = GetComponent<Animator>();    //��ȡ������

        stateTable = new Dictionary<System.Type, IState>(states.Length);    //״̬�ֵ�

        input = GetComponent<PlayerInput>();    //��ȡ������

        player = GetComponent<PlayerController>();  //��ȡ������

        //״̬����ʼ��
        foreach(PlayerState state in states)
        {
            state.Init(animator,input,player,this);
            stateTable.Add(state.GetType(), state);
        }
    }

    //��ʼ��״̬ΪIdle
    private void Start()
    {
        SwitchOn(stateTable[typeof(PlayerState_Idle)]);
    }
}
