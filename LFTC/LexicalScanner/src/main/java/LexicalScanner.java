import org.apache.commons.lang3.tuple.Pair;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

/**
 * created by bnorbert on 19,10,2017
 * bnorbertcristian@gmail.com
 */
public class LexicalScanner {

    private static final String         SPECIAL_CHARACTERS_FILE     = "specialCharacters.csv";
    private static final String         KEYWORDS_FILE               = "keywords.csv";
    private static final ClassLoader    CLASS_LOADER                = ClassLoader.getSystemClassLoader();

    private List<Integer>   begPositions;
    private List<Integer>   lineNumbers;
    private Set<String>     specialCharacters;
    private Set<String>     keywords;
    private CodesMap        codesMap;
    private Integer         currentCodeTS = 0;

    public LexicalScanner() throws IOException {
        this.codesMap = new CodesMap();
        this.specialCharacters = loadSpecialCharacters();
        this.keywords = loadKeywords();
    }

    public Pair<List<Pair<Integer,Integer>>, Map<String, Integer>> scan(BufferedReader reader) {

        begPositions = new ArrayList<>();
        lineNumbers = new ArrayList<>();

        List<Pair<Integer, Integer>> pif = new ArrayList<>();
        Map<String, Integer> symbolTable = new TreeMap<>();

        List<String> lines = reader.lines().collect(Collectors.toList());

        int lineNo = 0;
        for (String line : lines) {
            for (int i = 0; i < line.length(); ++i) {
                char ch = line.charAt(i);
                int after = 0;
                if(ch == ' ') continue;
                if (Character.isLetter(ch)) {
                    after = getIdxAfter(line, i, Character::isLetter);
                    String word = line.substring(i, after);

                    if (keywords.contains(word)) {
                        pif.add(Pair.of(codesMap.getCode(word), 0));
                    } else {
                        symbolTable.computeIfAbsent(word, k -> ++currentCodeTS);
                        pif.add(Pair.of(codesMap.getIdCode(), symbolTable.get(word)));
                    }
                } else if (Character.isDigit(ch)) {
                    after = getIdxAfter(line, i, Character::isDigit);
                    String constValue = line.substring(i, after);

                    symbolTable.computeIfAbsent(constValue, k -> ++currentCodeTS);
                    pif.add(Pair.of(codesMap.getConstCode(), symbolTable.get(constValue)));
                } else if (specialCharacters.contains("" + ch)) {
                    after = getIdxAfter(line, i, c -> specialCharacters.contains("" + c));
                    String element = line.substring(i, after);
                    element = element.trim();

                    pif.add(Pair.of(codesMap.getCode(element), 0));
                } else {
                    throw new RuntimeException(String.format("This charachter (at position %d) is not permitted!", i));
                }
                lineNumbers.add(lineNo);
                begPositions.add(i);
                i = after - 1;
            }
            ++lineNo;
        }
        verifyPIF(pif);

        return Pair.of(pif,symbolTable);
    }

    public void verifyPIF(List<Pair<Integer,Integer>> pif){
        for(int i=0;i<pif.size()-1;++i){
            if(pif.get(i).getValue()!=0 && pif.get(i+1).getValue()!=0)
                throw new RuntimeException(String.format("There is inconsistency in the file line %d at %d",lineNumbers.get(i)+1,begPositions.get(i)+1));
        }
    }

    private int getIdxAfter(String line, int i, Predicate<Character> verifier) {

        int idx = i;
        while (idx < line.length() && verifier.test(line.charAt(idx))) ++idx;
        return idx;
    }

    private Set<String> loadKeywords() throws FileNotFoundException {
        return new BufferedReader(new FileReader(CLASS_LOADER.getResource(KEYWORDS_FILE).getFile()))
                .lines()
                .collect(Collectors.toSet());
    }

    private Set<String> loadSpecialCharacters() throws FileNotFoundException {
        return new BufferedReader(new FileReader(CLASS_LOADER.getResource(SPECIAL_CHARACTERS_FILE).getFile()))
                .lines()
                .collect(Collectors.toSet());
    }
}
