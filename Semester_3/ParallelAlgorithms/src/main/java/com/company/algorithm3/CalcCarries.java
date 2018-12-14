package com.company.algorithm3;

public class CalcCarries implements Runnable {

    private int from;
    private int to;
    private int[] num1;
    private int[] num2;
    private CarryType[] carries;
    private CarryType carry_sum = CarryType.MAYBE;
    private CarryType total;


    CalcCarries(int from, int to, int[] num, int[] num2, CarryType[] carries) {
        this.from = from;
        this.to = to;
        this.num1 = num;
        this.num2 = num2;
        this.carries = carries;
    }

    public static CarryType sumCarries(CarryType carry1, CarryType carry2) {
        if (carry2 != CarryType.MAYBE)
            return carry2;
        else
            return carry1;
    }

    public CarryType sumCarries(int fromIndex, int toIndex) {
        CarryType carryFolder = CarryType.MAYBE;
        int sum;
        for (int i = fromIndex; i < toIndex; i++) {
            if ((sum = num1[i] + num2[i]) < 9)
                carries[i] = CarryType.NEVER;
            else if (sum == 9)
                carries[i] = CarryType.MAYBE;
            else
                carries[i] = CarryType.CARRY;
            carryFolder = sumCarries(carryFolder, carries[i]);
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
                Tree root = new Tree(1, Main.threadsAmount);
                root.treeSetup(Main.prefixes, 1, Main.threadsAmount);
                root.upsweep();
                root.downsweep(CarryType.MAYBE);
                Main.threadsFinished = 0;
                Main.synchronizer.notifyAll();
            }
        }
        // There cannot be any carry at 1's prefix:
        if (from == 0)
            total = CarryType.NEVER;
        else
            total = Main.prefixes[from / Main.interval];
        // Set final carries:
        carries[from] = sumCarries(total, carries[from]);
        for (int i = from + 1; i < to; i++)
            carries[i] = sumCarries(carries[i - 1], carries[i]);

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
                Main.result[i] = (Main.num1[i] + Main.num2[i] + (Main.carries[i - 1] == CarryType.CARRY ? 1 : 0)) % 10;
        }

    }
}
