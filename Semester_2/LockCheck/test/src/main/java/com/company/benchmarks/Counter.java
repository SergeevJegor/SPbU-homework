package com.company.benchmarks;

public class Counter implements Runnable {

    private MyLock lock;
    private int counter;
    private int incAmount;


    public Counter(MyLock inputLock, int incrementAmount) {
        lock = inputLock;
        incAmount = incrementAmount;
    }

    public int getCounter() {
        return counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < incAmount; i++) {
            lock.lock();
            try {
                counter++;
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }
        }
    }
}
