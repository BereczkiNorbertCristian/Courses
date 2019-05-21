package vacuum;

public class ActionSuckDirt extends VacuumAction {

    public VacuumState execute(VacuumAgent agent, VacuumState state) {
        System.out.println("Agent: " + agent.get_id() + " started sucking dirt...");
        state.remove_dirt(state.get_row(agent.get_id()), state.get_col(agent.get_id()));
        return state;
    }
}
