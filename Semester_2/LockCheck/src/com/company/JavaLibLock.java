package com.company;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class JavaLibLock implements Runnable {

    private final int incAmount;
    private int counter;
    private Lock lock = new ReentrantLock();

    public JavaLibLock(int incrementAmount) {
        incAmount = incrementAmount;
    }

    public int getCounter() {
        return counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < incAmount; i++) {
            try {
                if (lock.tryLock(100, TimeUnit.MILLISECONDS))
                    counter++;
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }
        }
    }
}
