package com.company.algorithm8;

public class Calculator implements Runnable {

    private int from;
    private int to;
    private int threadID;
    private PairType[] pairs;

    public Calculator(int from, int to, int threadID, PairType[] pairs) {
        this.from = from;
        this.to = to;
        this.threadID = threadID;
        this.pairs = pairs;
    }

    @Override
    public void run() {
        PairType folder = pairs[from];
        for (int i = from + 1; i < to; i++) {
            folder = folder.add(pairs[i]);
        }
        Main.prefixes[threadID] = folder;
    }
}
