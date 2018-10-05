package com.company;


public class WithoutLock implements Runnable {

    private final int incAmount;
    private int counter;

    public WithoutLock(int incrementAmount) {
        incAmount = incrementAmount;
    }

    public int getCounter() {
        return counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < incAmount; i++)
            counter++;
    }
}
