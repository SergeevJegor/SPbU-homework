package com.company.algorithm9;

import static java.lang.System.exit;

public class Main {
    public static final Object synchronizer = new Object();
    public static int threadsAmount = 4;
    public static int stringSize = 8;
    public static volatile IntBracketType[] prefixes;
    public static IntBracketType[] parsedString;
    public static int threadsFinished = 0;

    public static void main(String[] agrs) {
        setup(1, "((())))(");
        int interval = stringSize / threadsAmount;
        Thread[] threads = new Thread[threadsAmount];
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new Calculator(i * interval, Math.min((i + 1) * interval, stringSize), i, parsedString, prefixes));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        for (IntBracketType bracket : parsedString) {
            if (bracket.value == -1) {
                System.out.println("Wrong bracket. Abort");
                exit(1);
            }
        }
        if (parsedString[stringSize - 1].value > 0) {
            System.out.println("Wrong bracket. Abort");
            exit(1);
        }
        System.out.println("OK");
        exit(0);
    }

    public static void launch(int numOfThreads, String input) {
        setup(numOfThreads, input);
        int interval = stringSize / threadsAmount;
        Thread[] threads = new Thread[threadsAmount];
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new Calculator(i * interval, Math.min((i + 1) * interval, stringSize), i, parsedString, prefixes));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        for (IntBracketType bracket : parsedString) {
            if (bracket.value == -1) {
                System.out.println("Wrong bracket. Abort");
                exit(1);
            }
        }
        if (parsedString[stringSize - 1].value > 0) {
            System.out.println("Wrong bracket. Abort");
            exit(1);
        }
    }

    public static void setup(int numOfThreads, String input) {
        threadsFinished = 0;
        threadsAmount = numOfThreads;
        stringSize = input.length();
        prefixes = new IntBracketType[stringSize];
        for (int i = 0; i < stringSize; i++)
            prefixes[i] = new IntBracketType(0);
        parsedString = new IntBracketType[stringSize];
        // Parse string:
        input = input.replace('(', '1').replace(')', '0');
        String[] array = input.split("");
        for (int i = 0; i < stringSize; i++)
            parsedString[i] = new IntBracketType(Integer.parseInt(array[i]) == 0 ? -1 : 1);
    }

}
