package com.company.algorithm3;

public class Main {
    public static final Object synchronizer = new Object();
    public static int numberSize;
    public static int threadsAmount;
    public static int[] num1;
    public static int[] num2;
    public static volatile int[] result;
    public static int interval;
    public static volatile CarryType[] carries;
    public static volatile CarryType[] prefixes;
    public static volatile int threadsFinished = 0;

    public static void main(String[] args) {
        setup(8,
                8,
                "12356099",
                "00000001");
        CalcCarries[] calculators = new CalcCarries[threadsAmount];
        Thread[] threads = new Thread[threadsAmount];
        interval = Math.max(numberSize / threadsAmount, 1);
        for (int i = 0; i < threadsAmount; i++) {
            calculators[i] = new CalcCarries(i * interval, Math.min(interval * (i + 1), numberSize), num1, num2, carries);
            threads[i] = new Thread(calculators[i]);
            threads[i].start();
        }

        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        for (int i = numberSize - 1; i >= 0; i--) {
            System.out.print(result[i]);
        }

    }

    public static void launch(int sizeOfNumber, int amountOfThreads, String num1Str, String num2Str) {
        setup(sizeOfNumber, amountOfThreads, num1Str, num2Str);
        CalcCarries[] calculators = new CalcCarries[threadsAmount];
        Thread[] threads = new Thread[threadsAmount];
        interval = Math.max(numberSize / threadsAmount, 1);
        for (int i = 0; i < threadsAmount; i++) {
            calculators[i] = new CalcCarries(i * interval, Math.min(interval * (i + 1), numberSize), num1, num2, carries);
            threads[i] = new Thread(calculators[i]);
            threads[i].start();
        }

        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void setup(int sizeOfNumber, int amountOfThreads, String num1Str, String num2Str) {
        numberSize = sizeOfNumber;
        threadsAmount = Math.min(amountOfThreads, sizeOfNumber);
        num1 = new int[numberSize];
        num2 = new int[numberSize];
        for (int i = 0; i < numberSize; i++) {
            num1[i] = num1Str.charAt(numberSize - i - 1) - '0';
            num2[i] = num2Str.charAt(numberSize - i - 1) - '0';
        }
        prefixes = new CarryType[threadsAmount];
        result = new int[numberSize];
        carries = new CarryType[numberSize];
        for (int i = 0; i < numberSize; i++) {
            carries[i] = new CarryType(CarryType.Carry.NEVER);
        }
    }

}