package vacuum;

import static vacuum.Constants.*;

public class VacuumState {

    private int[] agents_row = {0, 3};;
    private int[] agents_col = {0, 3};;
    private int[] agents_direction = {UP, UP};

    private int[][] ground = {
            {CLEAN, CLEAN, CLEAN, CLEAN},
            {CLEAN, DIRT, CLEAN, CLEAN},
            {CLEAN, CLEAN, DIRT, CLEAN},
            {CLEAN, CLEAN, DIRT, CLEAN}
    };

    public VacuumState() {
    }

    public int get_row(int id) {
        return agents_row[id];
    }

    public int get_col(int id) {
        return agents_col[id];
    }

    public int get_direction(int id) {
        return agents_direction[id];
    }

    public void set_row(int id, int new_row) {
        agents_row[id] = new_row;
    }

    public void set_col(int id, int new_col) {
        agents_col[id] = new_col;
    }

    public void set_direction(int id, int new_direction) {
        agents_direction[id] = new_direction;
    }

    public void remove_dirt(int row, int col) {
        this.ground[row][col] = CLEAN;
    }

    public int cell(int row, int col) {
        return ground[row][col];
    }

    // before calling this functiono please call is_wall_ahead
    public boolean is_agent_ahead(int id, int next_row, int next_col) {
        if(agents_row[1-id] == next_row && agents_col[1-id] == next_col) return true;
        return false;
    }

    public boolean is_wall_ahead(int next_row, int next_col) {
        if(next_row < 0 || next_row >= ground.length) return true;
        if(next_col < 0 || next_col >= ground[0].length) return true;
        if(ground[next_row][next_col] == WALL) return true;
        return false;
    }

    public boolean is_done() {
        boolean done = true;
        for(int i=0;i<ground.length;++i) {
            for(int j=0;j<ground[i].length;++j) {
                if(ground[i][j] == DIRT) done = false;
            }
        }
        return done;
    }


    // Methods for debugging purposes
    public int get_dirts() {
        int ret = 0;
        for(int i=0;i<ground.length;++i) {
            for(int j=0;j<ground[i].length;++j) {
                if(ground[i][j] == DIRT) ret++;
            }
        }
        return ret;
    }

    public void show_state() {
        System.out.println("Showing state:");
        for(int i=0;i<ground.length;++i) {
            for (int j = 0; j < ground[i].length; ++j) {
                System.out.print(ground[i][j]);
            }
            System.out.println();
        }
    }
}
