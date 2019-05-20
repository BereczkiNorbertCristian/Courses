

import jade.core.Agent;
import jade.core.AID;
import jade.domain.FIPAAgentManagement.*;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;

import jade.core.Runtime;
import jade.core.ProfileImpl;
import jade.wrapper.*;

import java.util.Random;


public class ShipGame extends Agent {

    private static boolean IAmTheCreator = true;

    private AID initiator = null;

    protected void setup() {
        System.out.println(getLocalName()+" STARTED");
        Object[] args = getArguments();
        if (args != null && args.length > 0) {
            initiator = new AID((String) args[0], AID.ISLOCALNAME);
        }

        try {
            // create the agent descrption of itself
            DFAgentDescription dfd = new DFAgentDescription();
            dfd.setName(getAID());
            // register the description with the DF
            DFService.register(this, dfd);
            System.out.println(getLocalName()+" REGISTERED WITH THE DF");
        } catch (FIPAException e) {
            e.printStackTrace();
        }

        if (IAmTheCreator) {
            IAmTheCreator = false;  // next agent in this JVM will not be a creator

            // create another two ThanksAgent
            String t1AgentName = "Player1";
            String t2AgentName = "Player2";

            try {
                AgentContainer container = (AgentContainer)getContainerController(); // get a container controller for creating new agents
                AgentController t1= container.createNewAgent(t1AgentName, "ShipGame", null);
                t1.start();
                System.out.println(getLocalName() + " CREATED AND STARTED NEW PLAYER:" + t1AgentName);
            } catch (Exception any) {
                any.printStackTrace();
            }

            try {
                AgentContainer container = (AgentContainer)getContainerController(); // get a container controller for creating new agents
                AgentController t2 = container.createNewAgent(t2AgentName, "ShipGame", null);
                t2.start();
                System.out.println(getLocalName() + " CREATED AND STARTED NEW PLAYER:" + t2AgentName);
            } catch (Exception e2) {
                e2.printStackTrace();
            }

            ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
            msg.setContent("ACTIVATE");

            msg.addReceiver(new AID(t1AgentName, AID.ISLOCALNAME));
            msg.addReceiver(new AID(t2AgentName, AID.ISLOCALNAME));

            send(msg);
            System.out.println(getLocalName()+" sent ACTIVATION messages agents");
        }

        addBehaviour(new CyclicBehaviour(this) {

            int PLAYGROUND_BOUND = 4;
            int SHIP_LENGTH = 1;

            int[] state = new int[PLAYGROUND_BOUND];
            int[] opponent_state = new int[PLAYGROUND_BOUND];
            boolean done = false;
            boolean can_begin = false;
            boolean will_receive_activate_message = !getLocalName().equals("slim_shady");


            // INDEXING FROM 0 => [0,9]
            private void init_state() {
                for(int i=0;i<PLAYGROUND_BOUND;++i) state[i] = 0;
                for(int i=0;i<PLAYGROUND_BOUND;++i) opponent_state[i] = 0;

                Random rand = new Random();
                int beg_idx = rand.nextInt(PLAYGROUND_BOUND - SHIP_LENGTH);
                for(int i=beg_idx;i<beg_idx+SHIP_LENGTH;++i) state[i] = 1;
                System.out.println(getLocalName() + " has the ship beginning from " + Integer.toString(beg_idx));
            }

            public void action() {

                if(will_receive_activate_message) {
                    ACLMessage msg = blockingReceive();
                    can_begin = true;
                    init_state();
                    will_receive_activate_message = false;
                }

                // listen if a greetings message arrives
                if(can_begin && !done && getLocalName().equals("Player2")){

                    //RECEIVING
                    ACLMessage msg = blockingReceive();
                    System.out.println(getLocalName() + " received " + msg.getContent());
                    update_state(Integer.parseInt(msg.getContent()));

                    //SENDING
                    ACLMessage reply = new ACLMessage(ACLMessage.INFORM);
                    reply.addReceiver(new AID("Player1", AID.ISLOCALNAME));
                    reply.setContent(Integer.toString(get_next_shot()));
                    send(reply);
                }
                if(can_begin && !done && getLocalName().equals("Player1")) {

                    //SENDING
                    ACLMessage sending_message = new ACLMessage(ACLMessage.INFORM);
                    sending_message.addReceiver(new AID("Player2", AID.ISLOCALNAME));
                    sending_message.setContent(Integer.toString(get_next_shot()));
                    send(sending_message);

                    //RECEIVING
                    if(!done) {
                        ACLMessage msg = blockingReceive();
                        System.out.println(getLocalName() + " received " + msg.getContent());
                        update_state(Integer.parseInt(msg.getContent()));
                    }
                }
            }

            private void update_state(int idx) {
                if(idx == -1) {
                    System.out.println(getLocalName() + " WON THE GAME!!");
                    done = true;
                }
                else state[idx] = 0;
            }

            // -1 means that it cannot shoot anymore and this player lost the game
            private int get_next_shot() {
                //VERIFY
                boolean found_one = false;
                for(int i=0;i<PLAYGROUND_BOUND;++i) if(state[i] == 1) found_one=true;
                if(!found_one) {
                    done=true;
                    System.out.println(getLocalName() + " LOST THE GAME!!");
                    return -1;
                }
                else {
                    Random rand = new Random();
                    int shooting_pos = rand.nextInt(PLAYGROUND_BOUND);
                    while(opponent_state[shooting_pos] == 1) {
                        shooting_pos = rand.nextInt(PLAYGROUND_BOUND);
                    }
                    opponent_state[shooting_pos] = 1;
                    return shooting_pos;
                }
            }
        });
    }

    protected void takeDown() {
        // Deregister with the DF
        try {
            DFService.deregister(this);
            System.out.println(getLocalName()+" DEREGISTERED WITH THE DF");
        } catch (FIPAException e) {
            e.printStackTrace();
        }
    }
}
