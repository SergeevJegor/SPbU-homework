package com.company;

import java.util.concurrent.atomic.AtomicBoolean;

public class TASLock implements MyLock {

    private AtomicBoolean state = new AtomicBoolean(false);


    @Override
    public void lock(int threadID) {
        while (state.getAndSet(true)) {
            // Waiting...
        }
    }

    @Override
    public void unlock(int threadID) {
        state.set(false);
    }
}
