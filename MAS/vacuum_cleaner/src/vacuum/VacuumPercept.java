package vacuum;


public class VacuumPercept {

    private boolean dirt;
    private boolean wall;
    private boolean agent_ahead;

    VacuumPercept() {
        this.dirt = false;
        this.wall = false;
        this.agent_ahead = false;
    }

    public void set_dirt(boolean dirt) {
        this.dirt = dirt;
    }

    public void set_wall(boolean wall) {
        this.wall = wall;
    }

    public void set_agent_ahead(boolean agent_ahead) {
        this.agent_ahead = agent_ahead;
    }

    public boolean see_dirt() {
        return dirt;
    }

    public boolean see_wall() {
        return wall;
    }

    public boolean see_agent_ahead() {
        return agent_ahead;
    }
}
