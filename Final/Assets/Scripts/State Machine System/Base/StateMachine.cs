using System.Collections;
using System.Collections.Generic;
using UnityEngine;


//״̬������
public class StateMachine : MonoBehaviour
{
    IState currentState;    //��ǰ״̬�ӿ�

    //״̬�ֵ䣬���㴫�����״̬
    //��Ϊ״̬��type����Ϊ����Ϊÿ��state������һ��entity�����Զ��ڲ�ͬ��state����type�ǲ�ͬ�ģ�����ͨ��typeΨһ����state����ֵΪ����state
    protected Dictionary<System.Type, IState> stateTable;  
 

    //����״̬�߼�
    void Update()
    {
        currentState.LogicUpdate();     
    }

    //����״̬��������
    void FixedUpdate()
    {
        currentState.PhysicUpdate();    
    }


    //����һ����״̬
    protected void SwitchOn(IState newState)
    {
        currentState = newState;
        currentState.Enter();
    }

    //�л�״̬
    public void SwitchState(IState newState)
    {
        //���˳���ǰ״̬����ת����״̬
        currentState.Exit();
        SwitchOn(newState);
    }


    //�л�״̬������2��
    public void SwitchState(System.Type newStateType)
    {
        SwitchState(stateTable[newStateType]);
    }
}
