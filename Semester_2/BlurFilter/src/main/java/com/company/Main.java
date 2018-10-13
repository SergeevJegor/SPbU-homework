package com.company;


public class Main {

    private static final int RADIUS_SIZE = 4;
    private static final int THREADS_AMOUNT = 8;


    public static void main(String[] args) {
        ImageConverter converter = new ImageConverter("big", RADIUS_SIZE);
        converter.startThreads(ProcessingType.HORIZONTAL, THREADS_AMOUNT);
        converter.writeBlurredImage();
    }

}
