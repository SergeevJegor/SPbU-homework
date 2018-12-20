package com.company.parallel_scan;

public class Tree<T extends ValueType> {

    private T value;
    private Tree<T> leftSubtree;
    private Tree<T> rightSubtree;
    private int leftBound;
    private int rightBound;

    public Tree(int leftBound, int rightBound) {
        this.leftBound = leftBound;
        this.rightBound = rightBound;
    }

    public void treeSetup(T[] carries, int leftBound, int rightBound) {
        if (leftBound != rightBound) {
            int mid = leftBound + (rightBound - leftBound + 1) / 2 - 1;
            leftSubtree = new Tree<T>(leftBound, mid);
            rightSubtree = new Tree<T>(mid + 1, rightBound);
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

    public T upsweep() {
        if (value == null) {
            class Upsweep implements Runnable {
                Tree<T> tree;
                T returnValue;

                public Upsweep(Tree<T> tree) {
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
            return value = (T) runLeft.returnValue.add(runRight.returnValue);
        } else
            return value;
    }

    public void downsweep(T[] array, T carryFolder) {
        value = carryFolder;
        if (leftBound == rightBound) {
            array[leftBound - 1] = value;
            return;
        }
        T val = (T) value.add(leftSubtree.value);
        Thread threadLeft = new Thread(() -> leftSubtree.downsweep(array, value));
        threadLeft.start();
        rightSubtree.downsweep(array, val);
        try {
            threadLeft.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


}
