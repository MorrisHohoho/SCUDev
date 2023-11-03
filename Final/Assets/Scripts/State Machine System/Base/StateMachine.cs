using System.Collections;
using System.Collections.Generic;
using UnityEngine;


//状态机基类
public class StateMachine : MonoBehaviour
{
    IState currentState;    //当前状态接口

    //状态字典，方便传入具体状态
    //键为状态的type（因为我们为每个state创建了一个entity，所以对于不同的state，其type是不同的，可以通过type唯一区分state），值为具体state
    protected Dictionary<System.Type, IState> stateTable;  
 

    //更新状态逻辑
    void Update()
    {
        currentState.LogicUpdate();     
    }

    //更新状态物理特性
    void FixedUpdate()
    {
        currentState.PhysicUpdate();    
    }


    //开启一个新状态
    protected void SwitchOn(IState newState)
    {
        currentState = newState;
        currentState.Enter();
    }

    //切换状态
    public void SwitchState(IState newState)
    {
        //先退出当前状态，再转入新状态
        currentState.Exit();
        SwitchOn(newState);
    }


    //切换状态（过载2）
    public void SwitchState(System.Type newStateType)
    {
        SwitchState(stateTable[newStateType]);
    }
}
