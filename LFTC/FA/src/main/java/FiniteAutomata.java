import org.apache.commons.lang3.tuple.Pair;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

/**
 * created by bnorbert on 31,10,2017
 * bnorbertcristian@gmail.com
 */
public class FiniteAutomata {

    private static final ClassLoader    CLASS_LOADER    = ClassLoader.getSystemClassLoader();
    private static final String         FILENAME        = "input.in";

    private List<String> states;
    private Set<String> finalStates ;
    private String  startState = null;
    private List<String> alphabet;
    private Map<Pair<String,String>,List<String>> transitions;

    public FiniteAutomata() throws FileNotFoundException {
        loadAutomaton();
    }

    public boolean testSequence(List<String> sequence){
        return dfsSearch(startState,0,sequence);
    }

    private boolean dfsSearch(String state,int seqIdx,List<String> sequence){

        if(sequence.size() == seqIdx && finalStates.contains(state))
            return true;
        if(sequence.size() == seqIdx)
            return false;
        Pair<String,String> pr = Pair.of(state,sequence.get(seqIdx));
        if (!transitions.containsKey(pr))
            return false;
        boolean foundOneValid = false;
        for(String nextState : transitions.get(pr)){
            foundOneValid |= dfsSearch(nextState,seqIdx+1,sequence);
        }
        return foundOneValid;
    }

    @Override
    public String toString(){
        StringBuilder builder = new StringBuilder();
        builder.append("Start State: ").append(startState).append("\n");
        builder.append("States:\n");
        for(String state : states){
            builder.append(state).append(" ");
        }
        builder.append("\n");
        builder.append("Final States:\n");
        for(String finalState : finalStates){
            builder.append(finalState).append(" ");
        }
        builder.append("\n");
        builder.append("Alphabet:\n");
        builder.append(alphabet.toString());
        builder.append("\nTransitions:\n");
        for(Pair<String,String> key : transitions.keySet()){
            for(String nextState : transitions.get(key)){
                builder.append(key.getLeft()).append(" ");
                builder.append(key.getRight()).append(" ");
                builder.append(nextState).append("\n");
            }
        }
        return builder.toString();
    }

    private void loadAutomaton() throws FileNotFoundException {

        Scanner scanner = new Scanner(getReader());
        states = readStates(scanner);
        finalStates = readFinalStates(scanner);
        startState = scanner.next();
        alphabet = readStates(scanner);
        transitions = readTransitions(scanner);
    }

    private Map<Pair<String,String>,List<String>> readTransitions(Scanner scanner){

        Map<Pair<String,String>,List<String>> ret = new HashMap<>();
        int noTransitions = scanner.nextInt();
        scanner.nextLine();
        for(int i=0;i<noTransitions;++i){
            String[] line = scanner.nextLine().split(" ");
            Pair<String,String> pr = Pair.of(line[0],line[1]);
            ret.putIfAbsent(pr,new ArrayList<>());
            ret.get(pr).add(line[2]);
        }
        return ret;
    }

    private Set<String> readFinalStates(Scanner scanner){
        int noStates = scanner.nextInt();
        Set<String> ret = new HashSet<>();
        for(int i=0;i<noStates;++i){
            ret.add(scanner.next());
        }
        return ret;
    }

    private List<String> readStates(Scanner scanner){
        int noStates = scanner.nextInt();
        List<String> ret = new ArrayList<>(noStates);
        for(int i=0;i<noStates;++i){
            ret.add(scanner.next());
        }
        return ret;
    }

    private BufferedReader getReader() throws FileNotFoundException {
        return new BufferedReader(new FileReader(CLASS_LOADER.getResource(FILENAME).getFile()));
    }

}
