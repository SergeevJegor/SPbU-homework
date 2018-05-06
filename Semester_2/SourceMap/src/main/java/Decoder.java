import java.util.ArrayList;

public class Decoder {
    private String data;

    Decoder(String input) {
        data = input;
    }

    // We use symbol's index to decode BASE64 symbol:
    static private final String decodingString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static private int decodeBase64(char c) {
        return decodingString.indexOf(c);
    }

    private ArrayList<Integer> decodingResult;

    public ArrayList<Integer> getDecodingResult() {
        decode();
        return decodingResult;
    }

    private void decode() {
        // Decoding BASE64 string to binary string:
        String binaryRepresentation = "";
        for (char c : data.toCharArray()) {
            // We have total 6 bits so format is "%6s":
            binaryRepresentation += String.format("%6s", Integer.toBinaryString(decodeBase64(c))).replace(' ', '0');
        }
        /* SourceMap decoding:
         *  binary[pointer] -- continuation bit
         *  binary[pointer + 5] -- sign bit
         *  all remaining bits -- value
         *  *lets name pointer as "currentSymbol"
         */
        decodingResult = new ArrayList<>();
        int currentSymbol = 0;
        int sign;
        while (currentSymbol != binaryRepresentation.length()) {
            String str = binaryRepresentation.substring(currentSymbol + 1, currentSymbol + 5);
            sign = (int) binaryRepresentation.charAt(currentSymbol + 5);
            // If continuation bit is 1, take more bits:
            while (binaryRepresentation.charAt(currentSymbol) == '1') {
                currentSymbol += 6;
                // Now we have no sign bit, so we add whole string except continuation bit to the beginning (more valuable bits):
                str = binaryRepresentation.substring(currentSymbol + 1, currentSymbol + 6) + str;
            }
            str = sign == '1' ? '-' + str : str;
            decodingResult.add(Integer.parseInt(str, 2));
            currentSymbol += 6;
        }
    }
}
