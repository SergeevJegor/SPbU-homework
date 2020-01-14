package com.company.algorithm3;

import com.company.parallel_scan.Tree;

public class CalcCarries implements Runnable {

    private int from;
    private int to;
    private int[] num1;
    private int[] num2;
    private CarryType[] carries;
    private CarryType total = new CarryType(CarryType.Carry.MAYBE);


    CalcCarries(int from, int to, int[] num, int[] num2, CarryType[] carries) {
        this.from = from;
        this.to = to;
        this.num1 = num;
        this.num2 = num2;
        this.carries = carries;
    }

    public CarryType sumCarries(int fromIndex, int toIndex) {
        CarryType carryFolder = new CarryType(CarryType.Carry.MAYBE);
        int sum;
        for (int i = fromIndex; i < toIndex; i++) {
            if ((sum = num1[i] + num2[i]) < 9)
                carries[i].value = CarryType.Carry.NEVER;
            else if (sum == 9)
                carries[i].value = CarryType.Carry.MAYBE;
            else
                carries[i].value = CarryType.Carry.CARRY;
            carryFolder = carryFolder.add(carries[i]);
        }
        return carryFolder;
    }

    private void printArray(CarryType[] carries) {
        for (int i = from; i < to; i++) {
            System.out.println(Thread.currentThread().getId() - 12 + ": [" + i + "] " + carries[i]);
        }
    }

    @Override
    public void run() {
        Main.prefixes[from / Main.interval] = sumCarries(from, to);
        synchronized (Main.synchronizer) {
            Main.threadsFinished++;
            if (Main.threadsFinished != Main.threadsAmount) {
                try {
                    Main.synchronizer.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                Tree<CarryType> root = new Tree<CarryType>(1, Main.threadsAmount);
                root.treeSetup(Main.prefixes, 1, Main.threadsAmount);
                CarryType folder = root.upsweep();
                root.downsweep(Main.prefixes, folder);
                Main.threadsFinished = 0;
                Main.synchronizer.notifyAll();
            }
        }
        // There cannot be any carry at 1's prefix:
        if (from == 0)
            total.value = CarryType.Carry.NEVER;
        else
            total = Main.prefixes[from / Main.interval];
        // Set final carries:
        carries[from] = total.add(carries[from]);
        for (int i = from + 1; i < to; i++)
            carries[i] = carries[i - 1].add(carries[i]);

//        printArray(carries);

        synchronized (Main.synchronizer) {
            Main.threadsFinished++;
            if (Main.threadsFinished != Main.threadsAmount) {
                try {
                    Main.synchronizer.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                Main.synchronizer.notifyAll();
            }
        }

        for (int i = from; i < to; i++) {
            if (i == 0)
                Main.result[i] = (Main.num1[i] + Main.num2[i]) % 10;
            else
                Main.result[i] = (Main.num1[i] + Main.num2[i] + (Main.carries[i - 1].value == CarryType.Carry.CARRY ? 1 : 0)) % 10;
        }

    }
}