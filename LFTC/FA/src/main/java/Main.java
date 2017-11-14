import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collector;
import java.util.stream.Collectors;

/**
 * TODO: Find longest sequence
 * created by bnorbert on 31,10,2017
 * bnorbertcristian@gmail.com
 */
public class Main {

    public static void main(String[] args) throws FileNotFoundException {

        Scanner scanner = new Scanner(System.in);
        FiniteAutomata finiteAutomata = new FiniteAutomata("input.in");

        boolean goOn = true;
        while (goOn) {

            System.out.println(menu());
            String opt = scanner.nextLine();
            switch (opt) {
                case "0":
                    goOn = false;
                    break;
                case "1":
                    System.out.println(finiteAutomata.toString());
                    break;
                case "2":
                    System.out.println("Please insert a sequence (delimited by space):");
                    String seq = scanner.nextLine();
                    List<String> sequenceList = new ArrayList<>();
                    for(int i=0;i<seq.length();++i){
                        sequenceList.add(seq.substring(i,i+1));
                    }
                    int gotTo = finiteAutomata.testSequence(sequenceList);
                    System.out.println(String.format("The sequence is %b", gotTo == sequenceList.size()));
                    if (gotTo != sequenceList.size()) {
                        System.out.println(String.format("The sequence is valid until %d", gotTo));
                        System.out.println(String.format("Valid sequence until %s",seq.substring(0,gotTo)));
                    }
                    break;
                default:
                    System.out.println("Not valid option!");
            }
        }
    }

    private static String menu(){

        return new StringBuilder()
                .append("0. Exit\n")
                .append("1. Display automata state\n")
                .append("2. Test a sequence\n")
                .append("Insert your option:")
                .toString();
    }

}

