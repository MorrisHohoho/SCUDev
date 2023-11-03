//状态接口
public interface IState
{
    void Enter();  //进入状态

    void Exit();    //退出状态

    void LogicUpdate(); //逻辑更新

    void PhysicUpdate();    //实体物理特性更新
}
