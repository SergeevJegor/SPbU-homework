package com.company;

import java.util.concurrent.TimeUnit;

public class Main {

    private static final int NUMBER_OF_THREADS = 2;
    private static final int NUMBER_OF_INCREMENT = 100000000;


    public static void main(String[] args) throws Exception {

        WithoutLock withoutLock = new WithoutLock(NUMBER_OF_INCREMENT);
        JavaLibLock javaLibLock = new JavaLibLock(NUMBER_OF_INCREMENT);
        PetersonLock petersonLock = new PetersonLock(NUMBER_OF_INCREMENT);
        Thread[] withoutLockThread = new Thread[NUMBER_OF_THREADS];
        Thread[] javaLibLockThread = new Thread[NUMBER_OF_THREADS];
        Thread[] petersonLockThread = new Thread[NUMBER_OF_THREADS];

        for (int i = 0; i < NUMBER_OF_THREADS; i++) {
            withoutLockThread[i] = new Thread(withoutLock);
            withoutLockThread[i].start();
            javaLibLockThread[i] = new Thread(javaLibLock);
            javaLibLockThread[i].start();
            petersonLockThread[i] = new Thread(petersonLock);
            petersonLockThread[i].start();
        }

        TimeUnit.SECONDS.sleep(100);
        System.out.printf("Counter should be at %42d\n", NUMBER_OF_THREADS * NUMBER_OF_INCREMENT);
        System.out.printf("Counter value without lock: %35d\n", withoutLock.getCounter());
        System.out.printf("Counter value with standard java lib lock: %20d\n", javaLibLock.getCounter());
        System.out.printf("Counter value with implemented Peterson's lock: %15d\n", petersonLock.getCounter());

    }
}
