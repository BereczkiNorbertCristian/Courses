import org.apache.commons.lang3.tuple.Pair;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * created by bnorbert on 19,10,2017
 * bnorbertcristian@gmail.com
 */
public class CodesMap {

    private static final String         KEYWORDS_FILENAME   = "codes.tsv";
    private static final String         DELIM               = "@";
    private static final ClassLoader    CLASS_LOADER        = ClassLoader.getSystemClassLoader();

    private static final String ID_KEY      = "id";
    private static final String CONST_KEY   = "const";

    private Map<String, Integer> dictionary;

    public CodesMap() throws IOException {
        dictionary = loadData();
    }

    private Map<String, Integer> loadData() throws IOException {

        try (BufferedReader reader = new BufferedReader(
                new FileReader(CLASS_LOADER.getResource(KEYWORDS_FILENAME).getFile()))) {
            return reader
                    .lines()
                    .map(line -> Pair.of(line.split(DELIM)[0], Integer.parseInt(line.split(DELIM)[1])))
                    .collect(Collectors.toMap(Pair::getKey, Pair::getValue));
        }
    }

    public Integer getCode(String key) {
        return dictionary.get(key);
    }

    public boolean contains(char character) {
        return dictionary.containsKey("" + character);
    }

    public boolean contains(String string) {
        return dictionary.containsKey(string);
    }

    public Integer getIdCode() {
        return dictionary.get(ID_KEY);
    }

    public Integer getConstCode() {
        return dictionary.get(CONST_KEY);
    }
}
