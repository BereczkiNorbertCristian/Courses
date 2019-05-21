package vacuum;


/** An abstract class for actions in an agent environment. Each type of
 Action should be a separate subclass.  */
public abstract class VacuumAction {

    /** Update the state of the environment to reflect the effects of the
     agent performing the action. This implements the env: S x A -> S
     function. Note that in a multiagent environment, it is also
     important to know which agent is executing the action. */
    public abstract VacuumState execute(VacuumAgent agent, VacuumState sstate);

}