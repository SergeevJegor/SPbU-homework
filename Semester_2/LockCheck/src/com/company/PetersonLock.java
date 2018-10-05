package com.company;


public class PetersonLock implements Runnable {

    private final int incAmount;
    private int counter;
    private boolean[] want;
    private int waiting;
    private int threadID;


    public PetersonLock(int incrementAmount) {
        incAmount = incrementAmount;
        waiting = -1;
        want = new boolean[2];
        threadID = (int) Thread.currentThread().getId();
    }

    private void lock(int threadID) {
        int anotherThreadID = 1 - threadID;
        want[threadID] = true;
        waiting = threadID;
        while (want[anotherThreadID] && waiting == threadID) {
            // waiting...
        }
    }

    private void unlock(int threadID) {
        want[threadID] = false;
    }

    public int getCounter() {
        return counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < incAmount; i++) {
            lock(threadID);
            counter++;
            unlock(threadID);
        }
    }
}
