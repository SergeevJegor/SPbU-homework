package com.company.benchmarks;

//import com.company.TASLock;
//import com.company.TTASLock;
//import com.company.Counter;
//import static com.company.Main.NUMBER_OF_INCREMENT;
//import static com.company.Main.NUMBER_OF_THREADS;


public class Main  {

    public static final int NUMBER_OF_THREADS = 2;
    public static final int NUMBER_OF_INCREMENT = 10000000;
    

    static void tasTest() {
        Counter tasLockCounter = new Counter(new TASLock(), NUMBER_OF_INCREMENT);
        Thread[] tasLockThread = new Thread[NUMBER_OF_THREADS];
        for (int i = 0; i < NUMBER_OF_THREADS; i++) {
            tasLockThread[i] = new Thread(tasLockCounter);
            try {
                tasLockThread[i].join();
            } catch (Exception e) {
                e.printStackTrace();
            }
            tasLockThread[i].start();
        }
    }

    static void ttasTest() {
        Counter ttasLockCounter = new Counter(new TTASLock(), NUMBER_OF_INCREMENT);
        Thread[] ttasLockThread = new Thread[NUMBER_OF_THREADS];
        for (int i = 0; i < NUMBER_OF_THREADS; i++) {
            ttasLockThread[i] = new Thread(ttasLockCounter);
            try {
                ttasLockThread[i].join();
            } catch (Exception e) {
                e.printStackTrace();
            }
            ttasLockThread[i].start();
        }
    }

}
