package com.company;

import java.util.concurrent.ConcurrentSkipListSet;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Main {

    private static final int threadsAmount = 40;
    private static final int depth = 1;
    private static final String address = "http://hwproj.me";


    public static void main(String[] args) {
//        MyConcurrentQueue<String> urls = new MyConcurrentQueue<>();
//        MyThreadPool pool = new MyThreadPool(threadsAmount);
        ConcurrentSkipListSet<String> urls = new ConcurrentSkipListSet<>();
        ThreadPoolExecutor pool = new ThreadPoolExecutor(threadsAmount, threadsAmount, Long.MAX_VALUE, TimeUnit.NANOSECONDS, new LinkedBlockingQueue<>());
        Crawler task = new Crawler(address, 0, depth, pool, urls);
        pool.execute(task);

        while ((pool.getActiveCount() > 0) || (!pool.getQueue().isEmpty())) {
            try {
                Thread.currentThread().sleep(0, 1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        pool.shutdown();
    }


}
