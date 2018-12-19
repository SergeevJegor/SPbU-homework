package com.company;

import org.jsoup.nodes.Document;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;


public class Saver implements Runnable {
    private Document doc;

    public Saver(Document doc) {
        this.doc = doc;
    }

    @Override
    public void run() {
        System.out.println("Saving " + doc.location());
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter("resources/" + doc.location().replaceAll("//:", "_").replace('/', '_').replace(':', '_') + ".html"));
            writer.write(doc.toString());

        } catch (IOException e) {
        } finally {
            try {
                writer.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
