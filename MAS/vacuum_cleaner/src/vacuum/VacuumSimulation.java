package vacuum;


public class VacuumSimulation extends Thread {

    private VacuumEnvironment env = null;
    private VacuumAgent agent = null;

    public VacuumSimulation(
            VacuumEnvironment env,
            VacuumAgent agent
    ) {
        this.env = env;
        this.agent = agent;
    }

    private boolean is_complete() {
        return env.is_done();
    }

    public void run() {
        int it_no = 0;
        System.out.println("Dirts: " + env.get_dirts());
        env.show_state();
        env.init_first_lock(agent.get_id());
        while(!is_complete()) {

            VacuumPercept p = env.get_percept(agent);
            agent.see(p);
            VacuumAction action = agent.select_action();
            env.update_state(agent, action);
            agent.reset_perception();

            if(it_no % 100000000 == 0) {
                System.out.println(it_no);
                System.out.println("Dirts: " + env.get_dirts());
                env.show_state();
            }
            ++it_no;
        }
        env.show_state();
        System.out.println("DONE!");
    }
}
