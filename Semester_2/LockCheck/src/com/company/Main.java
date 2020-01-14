package com.company;


public class Main {

    public static final int NUMBER_OF_THREADS = 2;
    public static final int NUMBER_OF_INCREMENT = 10000000;


    public static void main(String[] args) throws Exception {

        Counter withoutLockCounter = new Counter(new WithoutLock(), NUMBER_OF_INCREMENT);
        Counter javaLibLockCounter = new Counter(new JavaLibLock(), NUMBER_OF_INCREMENT);
        Counter petersonLockCounter = new Counter(new PetersonLock(), NUMBER_OF_INCREMENT);

        Thread[] withoutLockThread = new Thread[NUMBER_OF_THREADS];
        Thread[] javaLibLockThread = new Thread[NUMBER_OF_THREADS];
        Thread[] petersonLockThread = new Thread[NUMBER_OF_THREADS];

        for (int i = 0; i < NUMBER_OF_THREADS; i++) {
            withoutLockThread[i] = new Thread(withoutLockCounter);
            withoutLockThread[i].join();
            withoutLockThread[i].start();
            javaLibLockThread[i] = new Thread(javaLibLockCounter);
            javaLibLockThread[i].join();
            javaLibLockThread[i].start();
            petersonLockThread[i] = new Thread(petersonLockCounter);
            petersonLockThread[i].join();
            petersonLockThread[i].start();
        }

        boolean flag = true;
        while (flag) {
            for (int i = 0; i < NUMBER_OF_THREADS; i++) {
                flag = withoutLockThread[i].isAlive() | javaLibLockThread[i].isAlive()/* & petersonLockThread[i].isAlive()*/;
            }
        }

        System.out.printf("Counter should be at %42d\n", NUMBER_OF_THREADS * NUMBER_OF_INCREMENT);
        System.out.printf("Counter value without lock: %35d\n", withoutLockCounter.getCounter());
        System.out.printf("Counter value with standard java lib lock: %20d\n", javaLibLockCounter.getCounter());
        System.out.printf("Counter value with implemented Peterson's lock: %15d\n", petersonLockCounter.getCounter());
    }
}
