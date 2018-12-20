package com.company.algorithm10;

import com.company.parallel_scan.Tree;

public class AnglesParse implements Runnable {
    private int from;
    private int to;
    private int threadID;
    private AngleType[] angles;
    private AngleType[] prefixes;

    public AnglesParse(int from, int to, int threadID, AngleType[] angles, AngleType[] prefixes) {
        this.from = from;
        this.to = to;
        this.threadID = threadID;
        this.angles = angles;
        this.prefixes = prefixes;
    }

    @Override
    public void run() {
        AngleType folder = new AngleType(0);
        for (int i = from; i < to; i++)
            folder = folder.add(angles[i]);
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
                Tree<AngleType> tree = new Tree<AngleType>(1, Main.threadsAmount);
                tree.treeSetup(prefixes, 1, Main.threadsAmount);
                tree.upsweep();
                tree.downsweep(prefixes, new AngleType(0));
                Main.threadsFinished = 0;
                Main.synchronizer.notifyAll();
            }
        }
        AngleType total;
        if (from != 0)
            total = prefixes[threadID];
        else
            total = new AngleType(0);
        angles[from] = angles[from].add(total);
        for (int i = from + 1; i < to; i++)
            angles[i] = angles[i - 1].add(angles[i]);
    }
}
