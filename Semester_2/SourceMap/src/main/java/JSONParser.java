import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonPrimitive;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

public class JSONParser {
    private String[] mappings;
    private String[] names;
    private String[] sources;

    public String[] getMappings() {
        return mappings;
    }

    public String[] getNames() {
        return names;
    }

    public String[] getSources() {
        return sources;
    }

    private static String readFile(String path, Charset encoding) throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        return new String(encoded, encoding);
    }

    private static String[] getStringArrayFromJsonField(JsonObject jsonObject, String fieldName) {
        JsonArray jsonArray = jsonObject.getAsJsonArray(fieldName);
        String[] strings = new String[jsonArray.size()];
        for (int i = 0; i < jsonArray.size(); i++) {
            strings[i] = jsonArray.get(i).getAsString();
        }
        return strings;
    }

    private static String[] getMappingsFromJson(JsonObject jsonObject) {
        JsonPrimitive jsonMappings= jsonObject.getAsJsonPrimitive("mappings");
        return jsonMappings.getAsString().split(",");
    }

    JSONParser(String filePath) throws IOException {
        String jsonString = readFile(filePath, Charset.defaultCharset());
        JsonObject jsonObject = new JsonParser().parse(jsonString).getAsJsonObject();

        mappings = getMappingsFromJson(jsonObject);
        names = getStringArrayFromJsonField(jsonObject, "names");
        sources = getStringArrayFromJsonField(jsonObject, "sources");
    }

}
