import vacuum.VacuumAgent;
import vacuum.VacuumEnvironment;
import vacuum.VacuumSimulation;
import vacuum.VacuumState;

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello World! Let's simulate some agents:");

        VacuumEnvironment environment = new VacuumEnvironment(new VacuumState());
        VacuumAgent agent1 = new VacuumAgent(0);
        VacuumAgent agent2 = new VacuumAgent(1);

        VacuumSimulation simulation = new VacuumSimulation(environment, agent1, agent2);
        simulation.run();
    }
}
