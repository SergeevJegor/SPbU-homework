package com.company.algorithm3;

public class Tree {
    private CarryType value;
    private Tree leftSubtree;
    private Tree rightSubtree;
    private int leftBound;
    private int rightBound;

    public Tree(int leftBound, int rightBound) {
        this.leftBound = leftBound;
        this.rightBound = rightBound;
    }

    public void treeSetup(CarryType[] carries, int leftBound, int rightBound) {
        if (leftBound != rightBound) {
            int mid = leftBound + (rightBound - leftBound + 1) / 2 - 1;
            leftSubtree = new Tree(leftBound, mid);
            rightSubtree = new Tree(mid + 1, rightBound);
            // Creating and starting new thread to create left subtree:
            Thread leftThread = new Thread(() -> leftSubtree.treeSetup(carries, leftBound, mid));
            leftThread.start();
            // Creating right subtree in this thread:
            rightSubtree.treeSetup(carries, mid + 1, rightBound);

            try {
                leftThread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else
            this.value = carries[leftBound - 1];
    }

    public CarryType upsweep() {
        if (value == null) {
            class Upsweep implements Runnable {
                Tree tree;
                CarryType returnValue;

                public Upsweep(Tree tree) {
                    this.tree = tree;
                }

                @Override
                public void run() {
                    returnValue = tree.upsweep();
                }
            }

            Upsweep runLeft = new Upsweep(leftSubtree);
            Upsweep runRight = new Upsweep(rightSubtree);
            Thread threadLeft = new Thread(runLeft);
            threadLeft.start();
            runRight.run();
            try {
                threadLeft.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            return CalcCarries.sumCarries(runLeft.returnValue, runRight.returnValue);
        } else
            return value;
    }

    public void downsweep(CarryType carryFolder) {
        value = carryFolder;
        if (leftBound == rightBound) {
            Main.prefixes[leftBound - 1] = value;
            return;
        }
        CarryType val = CalcCarries.sumCarries(value, leftSubtree.value);
        Thread threadLeft = new Thread(() -> leftSubtree.downsweep(value));
        threadLeft.start();
        rightSubtree.downsweep(val);
        try {
            threadLeft.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


}
