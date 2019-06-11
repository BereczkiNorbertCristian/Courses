package vacuum;

import static vacuum.Constants.*;

public class VacuumEnvironment {

    VacuumState env_state;

    public VacuumEnvironment(VacuumState env_state) {
        this.env_state = env_state;
    }

    public void init_first_lock(int id) {
        env_state.init_first_lock(id);
    }

    public void update_state(VacuumAgent agent, VacuumAction action) {
        env_state = action.execute(agent, env_state);
    }

    public VacuumPercept get_percept(VacuumAgent agent) {

        int agent_row = env_state.get_row(agent.get_id());
        int agent_col = env_state.get_col(agent.get_id());
        int agent_direction = env_state.get_direction(agent.get_id());

        VacuumPercept percept = new VacuumPercept();

        if(env_state.cell(agent_row, agent_col) == DIRT) percept.set_dirt(true);
        else percept.set_dirt(false);

        int next_row = agent_row + drow[agent_direction];
        int next_col = agent_col + dcol[agent_direction];

        if(env_state.is_wall_ahead(next_row, next_col)) percept.set_wall(true);
        else percept.set_wall(false);

        return percept;
    }

    public boolean is_done() {
        return env_state.is_done();
    }

    public int get_dirts() {
        return this.env_state.get_dirts();
    }

    public void show_state() {
        env_state.show_state();
    }
}
