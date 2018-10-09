package com.company;


import java.util.concurrent.TimeUnit;

public class PetersonLock implements MyLock {

    private boolean[] want;
    private int waiting;


    public PetersonLock() {
        waiting = -1;
        want = new boolean[2];
    }

    @Override
    public void lock() {
//        System.out.println("Locked " + (int) Thread.currentThread().getId() % 2);

        int threadID = (int) Thread.currentThread().getId() % 2;

        int anotherThreadID = 1 - threadID;
        want[threadID] = true;
        waiting = threadID;
        while (want[anotherThreadID] && waiting == threadID) {
            // Waiting...
        }
    }

    @Override
    public void unlock() {
//        System.out.println("UNLocked " + (int) Thread.currentThread().getId() % 2);
        int threadID = (int) Thread.currentThread().getId() % 2;
        want[threadID] = false;
    }

}
