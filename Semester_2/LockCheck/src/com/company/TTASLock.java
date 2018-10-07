package com.company;

import java.util.concurrent.atomic.AtomicBoolean;

public class TTASLock implements MyLock {

    private AtomicBoolean state = new AtomicBoolean(false);


    @Override
    public void lock() {
        while (true) {
            while (state.get()) {
                // Waiting...
            }
            if (!state.getAndSet(true)) {
                return;
            }
        }
    }

    @Override
    public void unlock() {
        state.set(false);
    }
}
