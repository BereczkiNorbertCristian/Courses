package vacuum;

import static vacuum.Constants.*;

public class ActionGoForward extends VacuumAction {

    public VacuumState execute(VacuumAgent agent, VacuumState state) {

        int agent_id = agent.get_id();

        int row = state.get_row(agent_id);
        int col = state.get_col(agent_id);
        int direction = state.get_direction(agent_id);

        state.set_row(agent_id,row + drow[direction]);
        state.set_col(agent_id,col + dcol[direction]);

        System.out.println("Agent: " + agent_id + " goes to: " + state.get_row(agent_id) + "," + state.get_col(agent_id));

        return state;
    }
}
