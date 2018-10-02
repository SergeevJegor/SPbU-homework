package com.company;

public class Incrementor implements Runnable {

    private final int incAmount;
    private int counter;

    public Incrementor(int incrementationAmount) {
        incAmount = incrementationAmount;
    }

    public int getCounter() {
        return counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < incAmount; i++) {
            counter++;
        }
    }
}
