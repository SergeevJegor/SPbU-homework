package com.company;

public class WithoutLock implements MyLock {

    @Override
    public void lock(int threadID) {
        // Do nothing
    }

    @Override
    public void unlock(int threadID) {
        // Do nothing
    }
}
