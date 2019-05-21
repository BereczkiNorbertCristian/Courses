package vacuum;


public class VacuumAgent {

    private int id;
    private boolean on_dirt;
    private boolean in_front_of_wall;
    private boolean is_agent_ahead;

    public VacuumAgent(int id) {
        this.id = id;
    }

    public int get_id() {
        return id;
    }

    public void see(VacuumPercept percept) {
        if(percept.see_dirt()) on_dirt = true;
        else on_dirt = false;

        if(percept.see_wall()) in_front_of_wall = true;
        else in_front_of_wall = false;

        if(!in_front_of_wall && percept.see_agent_ahead()) is_agent_ahead = true;
        else is_agent_ahead = false;
    }

    public VacuumAction select_action() {
        if(on_dirt) return new ActionSuckDirt();
        if(in_front_of_wall) return new ActionTurnRight();

        if(Math.random() > .5 && !is_agent_ahead) return new ActionGoForward();
        else return new ActionTurnRight();
    }

    public void reset_perception() {
        on_dirt = false;
        in_front_of_wall = false;
    }
}
