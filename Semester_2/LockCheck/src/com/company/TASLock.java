package com.company;

import java.util.concurrent.atomic.AtomicBoolean;

public class TASLock implements MyLock {

    private AtomicBoolean state = new AtomicBoolean(false);


    @Override
    public void lock() {
        while (state.getAndSet(true)) {
            // Waiting...
        }
    }

    @Override
    public void unlock() {
        state.set(false);
    }
}
