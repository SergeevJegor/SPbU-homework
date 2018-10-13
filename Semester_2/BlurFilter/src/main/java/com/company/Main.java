package com.company;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;

public class Main {

    private static final int RADIUS_SIZE = 3;
    private static final int THREADS_AMOUNT = 16;
    private static final String FILE_SRC = "img/";
    private static BufferedImage newImage;
    private static Filter filter;
    private static Thread[] filter_threads = new Thread[THREADS_AMOUNT];


    public static void main(String[] args) {
        try {
            setup();
        } catch (Exception e) {
            e.printStackTrace();
        }
        for (int i = 0; i < THREADS_AMOUNT; i++) {
            filter_threads[i] = new Thread(filter);
            filter_threads[i].start();
            try {
                filter_threads[i].join();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        try {
            ImageIO.write(newImage, "png", new File(FILE_SRC + "output.png"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void setup() throws Exception {
        File inputImage = new File(FILE_SRC + "input.png");
        BufferedImage image = ImageIO.read(inputImage);
        ImageIO.write(image, "png", new File(FILE_SRC + "output.png"));
        newImage = ImageIO.read(new File(FILE_SRC + "output.png"));
        filter = new Filter(image, newImage, ProcessingType.HORIZONTAL, RADIUS_SIZE, THREADS_AMOUNT);
    }
}
