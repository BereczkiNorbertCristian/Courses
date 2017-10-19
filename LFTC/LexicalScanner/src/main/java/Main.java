import org.apache.commons.lang3.tuple.Pair;

import java.io.*;
import java.util.List;
import java.util.Map;

/**
 * created by bnorbert on 19,10,2017
 * bnorbertcristian@gmail.com
 */
public class Main {

    private static final String         SOURCE_FILE_NAME    = "sourcefile.txt";
    private static final ClassLoader    CLASS_LOADER        = ClassLoader.getSystemClassLoader();

    public static void main(String[] args) throws IOException {

        BufferedReader sourceFileReader = readSourceFile();
        LexicalScanner lexicalScanner = new LexicalScanner();

        Pair<List<Pair<Integer, Integer>>, Map<String, Integer>> result =
                lexicalScanner.scan(sourceFileReader);

        List<Pair<Integer, Integer>> pif = result.getLeft();
        Map<String, Integer> symbolTable = result.getRight();

        System.out.println("PIF:");
        pif.stream().forEach(pr -> System.out.println(String.format("%d,%d", pr.getLeft(), pr.getRight())));
        System.out.println("SYMBOL TABLE:");
        symbolTable.entrySet().stream().forEach(entry -> System.out.println(String.format("%s->%d", entry.getKey(), entry.getValue())));
    }

    private static BufferedReader readSourceFile() throws FileNotFoundException {

        return new BufferedReader(new FileReader(CLASS_LOADER.getResource(SOURCE_FILE_NAME).getFile()));
    }
}
