package com.company;

import java.util.concurrent.Executor;

public class MyThreadPool implements Executor {
    private final MyConcurrentQueue<Runnable> queue = new MyConcurrentQueue<>();
    volatile boolean isActive = true;
    private Thread[] threads;
    private Task[] tasks;

    public MyThreadPool(int numOfThreads) {
        threads = new Thread[numOfThreads];
        tasks = new Task[numOfThreads];
        for (int i = 0; i < numOfThreads; i++) {
            tasks[i] = new Task();
            threads[i] = new Thread(tasks[i]);
            threads[i].start();
        }
    }

    @Override
    public void execute(Runnable runnable) {
        if (isActive) {
            queue.offer(runnable);
        }
    }

    public MyConcurrentQueue<Runnable> getQueue() {
        return queue;
    }

    public void shutdown() {
        isActive = false;
    }

    private final class Task implements Runnable {
        @Override
        public void run() {
            while (isActive) {
                Runnable nextTask = queue.poll();
                if (nextTask != null) {
                    nextTask.run();
                }
            }
        }
    }
}
