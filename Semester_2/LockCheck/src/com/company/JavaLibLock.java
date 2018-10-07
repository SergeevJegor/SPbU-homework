package com.company;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class JavaLibLock implements MyLock {

    private Lock javaLock = new ReentrantLock();


    @Override
    public void lock(int threadID) {
        javaLock.lock();
    }

    @Override
    public void unlock(int threadID) {
        javaLock.unlock();
    }
}
