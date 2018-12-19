package com.company;

import java.util.concurrent.ConcurrentSkipListSet;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Main {

    private static int threadsAmount = 4;
    private static final int depth = 1;
    private static final String address = "http://hwproj.me";

    public static void main(String[] args) {
        int[] threads = {1, 2, 4, 8};
        long[] times = new long[4];
        int iterations = 10;
        for (int i = 0; i < 4 * iterations; i++)
            System.out.print("_");
        System.out.println();
        for (int i = 0; i < 4; i++) {
            long sumTime = 0;
            for (int j = 0; j < iterations; j++) {
                long startTime = System.nanoTime();
                launch(threads[i]);
                long endTime = System.nanoTime();
                sumTime += endTime - startTime;
                System.out.print("=");
            }
            times[i] = sumTime / iterations;
        }
        System.out.println();
        for (int i = 0; i < 4; i++) {
            System.out.println(threads[i] + " threads: " + times[i]);
        }
    }

    public static void launch(int numOfThreads) {
        threadsAmount = numOfThreads;
        MyConcurrentQueue<String> urls = new MyConcurrentQueue<>();
        MyThreadPool pool = new MyThreadPool(threadsAmount);
//        ConcurrentSkipListSet<String> urls = new ConcurrentSkipListSet<>();
//        ThreadPoolExecutor pool = new ThreadPoolExecutor(threadsAmount, threadsAmount, Long.MAX_VALUE, TimeUnit.NANOSECONDS, new LinkedBlockingQueue<>());
        Counter counter = new Counter();
        Crawler task = new Crawler(address, 0, depth, pool, urls, counter);
        pool.execute(task);

        do {
            try {
                Thread.currentThread().sleep(0,1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } while ((task.getCounter().getCount() > 0) || (!pool.getQueue().isEmpty()));

        pool.shutdown();
    }
}
