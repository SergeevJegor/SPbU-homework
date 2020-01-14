package com.company;

import java.awt.*;
import java.awt.image.BufferedImage;


public class Filter implements Runnable {

    private BufferedImage newImage;
    private BufferedImage image;
    private int width;
    private int height;
    private ProcessingType direction;
    private int radius;
    private int threads;


    public Filter(BufferedImage img, BufferedImage newImg, int radiusSize, ProcessingType processingType, int numberOfThreads) {
        newImage = newImg;
        image = img;
        width = image.getWidth();
        height = image.getHeight();
        direction = processingType;
        radius = radiusSize;
        threads = numberOfThreads;
    }

    private void horizontalBlurFilter() {
        int linesToProcess = height / threads;
        for (int i = 0; i < linesToProcess; i++) {
            int row = i * threads + (int) Thread.currentThread().getId() % threads;
            for (int column = 0; column < width; column++) {
                int redChannel = 0;
                int greenChannel = 0;
                int blueChannel = 0;
                int pixelsCounted = 0;
                Color color;
                for (int y = row - radius; y < row + radius; y++) {
                    for (int x = column - radius; x < column + radius; x++) {
                        if (x >= 0 & x < width & y >= 0 & y < height & (x != column | y != row)) {
                            color = new Color(image.getRGB(x, y));
                            redChannel += color.getRed();
                            greenChannel += color.getGreen();
                            blueChannel += color.getBlue();
                            pixelsCounted++;
                        }
                    }
                }
                redChannel /= pixelsCounted;
                greenChannel /= pixelsCounted;
                blueChannel /= pixelsCounted;
                newImage.setRGB(column, row, new Color(redChannel, greenChannel, blueChannel).getRGB());
            }
        }
    }

    private void verticalBlurFilter() {
        int linesToProcess = width / threads;
        for (int row = 0; row < height; row++) {
            for (int i = 0; i < linesToProcess; i++) {
                int column = i * threads + (int) Thread.currentThread().getId() % threads;
                int redChannel = 0;
                int greenChannel = 0;
                int blueChannel = 0;
                int pixelsCounted = 0;
                Color color;
                for (int y = row - radius; y < row + radius; y++) {
                    for (int x = column - radius; x < column + radius; x++) {
                        if (x >= 0 & x < width & y >= 0 & y < height & (x != column | y != row)) {
                            color = new Color(image.getRGB(x, y));
                            redChannel += color.getRed();
                            greenChannel += color.getGreen();
                            blueChannel += color.getBlue();
                            pixelsCounted++;
                        }
                    }
                }
                redChannel /= pixelsCounted;
                greenChannel /= pixelsCounted;
                blueChannel /= pixelsCounted;
                newImage.setRGB(column, row, new Color(redChannel, greenChannel, blueChannel).getRGB());
            }
        }
    }

    @Override
    public void run() {
        if (direction == ProcessingType.HORIZONTAL) {
            horizontalBlurFilter();
        } else if (direction == ProcessingType.VERTICAL) {
            verticalBlurFilter();
        }
    }
}
