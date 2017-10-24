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
 * Class for doing lexical analysis for a custom made language
 *
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

    /**
     * Initializes the codes for the special symbols in the language
     * Loads the special characters from a resource file
     * Loads the keywords from another resource file
     *
     * @throws IOException
     */
    public LexicalScanner() throws IOException {
        this.codesMap = new CodesMap();
        this.specialCharacters = loadSpecialCharacters();
        this.keywords = loadKeywords();
    }

    /**
     * Scans the source file in the following way.
     * For every line we start parsing each token in the following way:
     *  - If the current character is a letter then we find the last character LI in this continuous sequence
     *  which begins with the current character and ends at LI and is formed only with letters. We consider this
     *  to be a token and we verify if it is a keyword or an identifier.
     *      - If it is an identifier then we put it in the symbol table (if it is not already there)
     *      and extract the code and put it in a pif along with the value in the symbold table.
     *      - If it is a keyword then we put in the pif a pair representing the code of the keyword and 0
     *  - If the current character is a digit the we find the last character LI in the continuous sequence
     *  which beings with the current character and ends at LI and is formed only with digits. We consider this
     *  a constant and we put it in the symbol table(if it is not there already) and in the pif we put a pair
     *  (constant code, value in symbol table)
     *  - If the current character is a special symbol then we go to the last character of that symbol with LI and
     *  put in the pif a pair (code of special symbol, 0)
     *
     *  We then jummp (LI- currentPos) because we have processed this part of the string.
     *
     * @param reader
     * @return a pair representing the Symbol Table and the PIF
     */
    public Pair<List<Pair<Integer,Integer>>, Map<String, Integer>> scan(BufferedReader reader) {

        begPositions = new ArrayList<>();
        lineNumbers = new ArrayList<>();
        currentCodeTS = 0;

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
                        if(word.length() > 250)
                            throw new RuntimeException("This identifier is longer than 250 characters");
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
                    throw new RuntimeException(String.format("This charachter (at position %d) %s is not permitted!", i, line.charAt(i)));
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

    /**
     * Verifies if a PIF is correct and if there has been any errors in the lexical analysis
     * If there are 2 consecutive values in the PIF then it means that there was an error.
     * Throws exception if error, containing the line and column in the source file at which the error occured.
     *
     * @param pif
     */
    public void verifyPIF(List<Pair<Integer,Integer>> pif){
        for(int i=0;i<pif.size()-1;++i){
            if(pif.get(i).getValue()!=0 && pif.get(i+1).getValue()!=0)
                throw new RuntimeException(String.format("There is inconsistency in the file line %d at %d",lineNumbers.get(i)+1,begPositions.get(i)+1));
        }
    }

    /**
     * Finds the last character which is valid in the current continuous string according with a verifier
     *
     * @param line
     * @param i
     * @param verifier
     * @return
     */
    private int getIdxAfter(String line, int i, Predicate<Character> verifier) {

        int idx = i;
        while (idx < line.length() && verifier.test(line.charAt(idx))) ++idx;
        return idx;
    }

    /**
     * Reads from a file the keywords
     *
     * @return
     * @throws FileNotFoundException
     */
    private Set<String> loadKeywords() throws FileNotFoundException {
        return new BufferedReader(new FileReader(CLASS_LOADER.getResource(KEYWORDS_FILE).getFile()))
                .lines()
                .collect(Collectors.toSet());
    }

    /**
     * Reads from a file the special characters
     *
     * @return
     * @throws FileNotFoundException
     */
    private Set<String> loadSpecialCharacters() throws FileNotFoundException {
        return new BufferedReader(new FileReader(CLASS_LOADER.getResource(SPECIAL_CHARACTERS_FILE).getFile()))
                .lines()
                .collect(Collectors.toSet());
    }
}
