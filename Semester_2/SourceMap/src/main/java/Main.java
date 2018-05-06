import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class Main {
    public static void main(String Args[]) throws IOException {
        String mapFilePath = new File("").getAbsolutePath() + "/src/main/resources/o.min.map";
        JSONParser jsonParser = new JSONParser(mapFilePath);

        String[] mappings = jsonParser.getMappings();
        String[] names = jsonParser.getNames();
        String[] sources = jsonParser.getSources();

        int currentInputCharIndex = 0;
        int currentOutputCharIndex = 0;
        int currentInputLineIndex = 0;
        int currentFileIndex = 0;
        int currentVariableNameIndex = 0;

        for (String s : mappings) {
            Decoder decoder = new Decoder(s);
            ArrayList<Integer> decodingResult = decoder.getDecodingResult();

            currentOutputCharIndex += decodingResult.get(0);
            currentFileIndex += decodingResult.get(1);
            currentInputLineIndex += decodingResult.get(2);
            currentInputCharIndex += decodingResult.get(3);
            if (decodingResult.size() == 5) {
                currentVariableNameIndex += decodingResult.get(4);
            }

            System.out.println("Symbol number " + currentOutputCharIndex + " maps to symbol at line " +
                    currentInputLineIndex + " column " + currentInputCharIndex + " at file " +
                    sources[currentFileIndex] + ", connected with variable " + names[currentVariableNameIndex]);
        }
    }
}
