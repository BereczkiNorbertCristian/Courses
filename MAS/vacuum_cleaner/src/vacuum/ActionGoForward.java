package vacuum;

import static vacuum.Constants.*;

public class ActionGoForward extends VacuumAction {

    public VacuumState execute(VacuumAgent agent, VacuumState state) {

        int agent_id = agent.get_id();

        int row = state.get_row(agent_id);
        int col = state.get_col(agent_id);
        int direction = state.get_direction(agent_id);

        int next_row = row + drow[direction];
        int next_col = col + dcol[direction];

        state.lock_cell(next_row, next_col);

        state.set_row(agent_id, next_row);
        state.set_col(agent_id, next_col);

        state.unlock_cell(row, col);

        System.out.println("Agent: " + agent_id + " goes to: " + state.get_row(agent_id) + "," + state.get_col(agent_id));

        return state;
    }
}
