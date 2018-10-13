package com.company;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;


public class ImageConverter {

    private static final String FILE_SRC = "img/";
    private static final String FILE_FORMAT = "png";
    private int radius;
    private String fileName;
    private BufferedImage image;
    private BufferedImage newImage;


    public ImageConverter(String nameOfFile, int radiusSize) {
        this.radius = radiusSize;
        this.fileName = nameOfFile;
        setup();
    }

    private void setup() {
        try {
            File inputImage = new File(FILE_SRC + fileName + "." + FILE_FORMAT);
            image = ImageIO.read(inputImage);
            // This write will create output file:
            ImageIO.write(image, FILE_FORMAT, new File(FILE_SRC + fileName + "Output." + FILE_FORMAT));
            newImage = ImageIO.read(new File(FILE_SRC + fileName + "Output." + FILE_FORMAT));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public void startThreads(ProcessingType processingType, int threadsAmount) {
        Filter filter = new Filter(image, newImage, radius, processingType, threadsAmount);
        Thread[] filter_threads = new Thread[threadsAmount];
        for (int i = 0; i < threadsAmount; i++) {
            filter_threads[i] = new Thread(filter);
            filter_threads[i].start();
            try {
                filter_threads[i].join();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public void writeBlurredImage(String fileName) {
        try {
            ImageIO.write(newImage, FILE_FORMAT, new File(FILE_SRC + fileName + "Output." + FILE_FORMAT));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
