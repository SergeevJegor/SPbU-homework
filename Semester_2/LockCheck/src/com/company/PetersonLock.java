package com.company;


public class PetersonLock implements MyLock {

    private boolean[] want;
    private int waiting;
    private int threadID;


    public PetersonLock() {
        waiting = -1;
        want = new boolean[2];
        threadID = (int) Thread.currentThread().getId();
    }

    @Override
    public void lock() {
        int anotherThreadID = 1 - threadID;
        want[threadID] = true;
        waiting = threadID;
        while (want[anotherThreadID] && waiting == threadID) {
            // waiting...
        }
    }

    @Override
    public void unlock() {
        want[threadID] = false;
    }

}
