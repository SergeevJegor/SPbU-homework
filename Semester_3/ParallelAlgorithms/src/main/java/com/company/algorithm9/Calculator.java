package com.company.algorithm9;

import com.company.parallel_scan.Tree;

public class Calculator implements Runnable {
    private int from;
    private int to;
    private int threadID;
    private IntBracketType[] brackets;
    private IntBracketType[] prefixes;

    public Calculator(int from, int to, int threadID, IntBracketType[] brackets, IntBracketType[] prefixes) {
        this.from = from;
        this.to = to;
        this.threadID = threadID;
        this.brackets = brackets;
        this.prefixes = prefixes;
    }

    @Override
    public void run() {
        IntBracketType folder = new IntBracketType(0);
        for (int i = from; i < to; i++)
            folder = folder.add(brackets[i]);
        prefixes[threadID] = folder;

        synchronized (Main.synchronizer) {
            Main.threadsFinished++;
            if (Main.threadsFinished != Main.threadsAmount) {
                try {
                    Main.synchronizer.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                Tree<IntBracketType> tree = new Tree<IntBracketType>(1, Main.threadsAmount);
                tree.treeSetup(prefixes, 1, Main.threadsAmount);
                folder = tree.upsweep();
                tree.downsweep(Main.prefixes, folder);
                Main.threadsFinished = 0;
                Main.synchronizer.notifyAll();
            }
            IntBracketType total;
            if (from != 0)
                total = prefixes[threadID];
            else
                total = new IntBracketType(0);
            brackets[from] = brackets[from].add(total);
            for (int i = from + 1; i < to; i++)
                brackets[i] = brackets[i - 1].add(brackets[i]);
        }
    }
}
