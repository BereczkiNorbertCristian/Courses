package vacuum;

public class ActionTurnRight extends VacuumAction {

    public VacuumState execute(VacuumAgent agent, VacuumState state) {
        state.set_direction(agent.get_id(),(state.get_direction(agent.get_id()) + 1) % 4);
        return state;
    }
}
