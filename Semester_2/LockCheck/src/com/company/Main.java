package com.company;

public class Main {

    private static final int NUMBER_OF_THREADS = 1000;
    private static final int NUMBER_OF_INCREMENT = 100000;


    public static void main(String[] args) throws Exception {

        Incrementor incremenator = new Incrementor(NUMBER_OF_INCREMENT);
        Thread[] threads = new Thread[NUMBER_OF_THREADS];

        for (Thread thread : threads) {
            thread = new Thread(incremenator);
            thread.start();
        }
        System.out.println("Counter should be at " + NUMBER_OF_THREADS * NUMBER_OF_INCREMENT);
        System.out.println("Current value: " + incremenator.getCounter());
    }
}
