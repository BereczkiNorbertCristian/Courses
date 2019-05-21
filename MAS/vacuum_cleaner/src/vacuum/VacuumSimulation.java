package vacuum;


public class VacuumSimulation {

    private VacuumEnvironment env = null;
    private VacuumAgent agent1 = null;
    private VacuumAgent agent2 = null;

    public VacuumSimulation(
            VacuumEnvironment env,
            VacuumAgent agent1,
            VacuumAgent agent2
    ) {
        this.env = env;
        this.agent1 = agent1;
        this.agent2 = agent2;
    }

    private boolean is_complete() {
        return env.is_done();
    }

    public void do_agent(VacuumAgent agent) {

        VacuumPercept p = env.get_percept(agent);
        agent.see(p);
        VacuumAction action = agent.select_action();
        env.update_state(agent, action);
        agent.reset_perception();
    }

    public void run() {
        int it_no = 0;
        System.out.println("Dirts: " + env.get_dirts());
        env.show_state();
        while(!is_complete()) {

            do_agent(agent1);
            do_agent(agent2);

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
