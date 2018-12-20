package com.company.algorithm8;

import com.company.parallel_scan.Tree;

public class Main {

    public static int threadsAmount;
    public static int pairsAmount;
    public static volatile int result;
    public static volatile PairType[] prefixes;
    public static PairType[] pairs;


    public static void main(String[] args) {
        setup(8, 4, null);
        int interval = pairsAmount / threadsAmount;
        Thread[] threads = new Thread[threadsAmount];
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new Calculator(i * interval, Math.min((i + 1) * interval, pairsAmount), i, pairs));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Tree<PairType> tree = new Tree<PairType>(1, pairsAmount);
        tree.treeSetup(pairs, 1, pairsAmount);
        result = tree.upsweep().b;
        System.out.println(result);
    }

    static void setup(int numOfThreads, int numOfPairs, PairType[] input) {
        threadsAmount = numOfThreads;
        pairsAmount = numOfPairs;
        result = 0;
        // pairs = input
        pairs = new PairType[]{new PairType(1, 2), new PairType(0, 3), new PairType(2, 4), new PairType(1, 5)};
        prefixes = new PairType[threadsAmount];
        for (int i = 0; i < threadsAmount; i++)
            prefixes[i] = new PairType(0, 0);
    }
}
