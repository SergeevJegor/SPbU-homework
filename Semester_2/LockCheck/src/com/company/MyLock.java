package com.company;

public interface MyLock {

    void lock(int threadID);

    void unlock(int threadID);
}
