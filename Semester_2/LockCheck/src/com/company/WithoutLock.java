package com.company;

public class WithoutLock implements MyLock {

    @Override
    public void lock() {
        // Do nothing
    }

    @Override
    public void unlock() {
        // Do nothing
    }
}
