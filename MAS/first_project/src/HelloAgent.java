import jade.content.onto.basic.Action;
import jade.core.Agent;
import jade.core.behaviours.SimpleBehaviour;

public class HelloAgent extends Agent {

    protected void setup() {
        addBehaviour(new SimpleBehaviour(this) {
            int n = 0;
            @Override
            public void action() {
                System.out.println("Hy, my name is: " + myAgent.getLocalName());
                ++n;
            }

            @Override
            public boolean done() {
                return n >= 5;
            }
        });
    }
}
