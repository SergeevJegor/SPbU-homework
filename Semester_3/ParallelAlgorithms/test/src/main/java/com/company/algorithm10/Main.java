package com.company.algorithm10;

import com.company.parallel_scan.Tree;

public class Main {
    public static final Object synchronizer = new Object();
    public static int threadsAmount = 8;
    public static int commandsAmount = 4;
    public static CommandType[] commands;
    public static AngleType[] angles;
    public static AngleType[] anglesPrefixes;
    public static CoordinatesType[] coordinates;
    public static volatile CoordinatesType result = new CoordinatesType(0, 0);
    public static volatile CoordinatesType[] coordinatesPrefixes;
    public static int threadsFinished = 0;

    public static void main(String[] agrs) {
        setup(2, 4,
                new CommandType[]{new CommandType(45, 20),
                        new CommandType(75, 10),
                        new CommandType(240, 5),
                        new CommandType(270, 22.8)});
        int interval = commandsAmount / threadsAmount;
        // Parse angles:
        Thread[] threads = new Thread[threadsAmount];
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new AnglesParse(i * interval, Math.min((i + 1) * interval, commandsAmount), i, angles, anglesPrefixes));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        // (angle, length) --> (x, y):
        coordinates = new CoordinatesType[commandsAmount];
        for (int i = 0; i < commandsAmount; i++) {
            coordinates[i] = new CoordinatesType(Math.cos(Math.toRadians(angles[i].value)) * commands[i].length,
                    Math.sin(Math.toRadians(angles[i].value)) * commands[i].length);
//            System.out.println(coordinates[i]);
        }
        // Parallel scan on coordinates:
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new Calculator(i * interval, Math.min((i + 1) * interval, commandsAmount), i, coordinates, coordinatesPrefixes));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Tree<CoordinatesType> tree = new Tree<>(1, threadsAmount);
        tree.treeSetup(coordinatesPrefixes, 1, threadsAmount);
        result = tree.upsweep();
        System.out.println(result);
    }

    public static void launch(int numOfThreads, int numOfCommands, CommandType[] input) {
        setup(numOfThreads, numOfCommands, input);
        int interval = commandsAmount / threadsAmount;
        // Parse angles:
        Thread[] threads = new Thread[threadsAmount];
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new AnglesParse(i * interval, Math.min((i + 1) * interval, commandsAmount), i, angles, anglesPrefixes));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        // (angle, length) --> (x, y):
        coordinates = new CoordinatesType[commandsAmount];
        for (int i = 0; i < commandsAmount; i++) {
            coordinates[i] = new CoordinatesType(Math.cos(Math.toRadians(angles[i].value)) * commands[i].length,
                    Math.sin(Math.toRadians(angles[i].value)) * commands[i].length);
//            System.out.println(coordinates[i]);
        }
        // Parallel scan on coordinates:
        for (int i = 0; i < threadsAmount; i++) {
            threads[i] = new Thread(new Calculator(i * interval, Math.min((i + 1) * interval, commandsAmount), i, coordinates, coordinatesPrefixes));
            threads[i].start();
        }
        try {
            for (int i = 0; i < threadsAmount; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Tree<CoordinatesType> tree = new Tree<>(1, threadsAmount);
        tree.treeSetup(coordinatesPrefixes, 1, threadsAmount);
        result = tree.upsweep();
    }

    public static void setup(int numOfThreads, int numOfCommands, CommandType[] input) {
        threadsFinished = 0;
        threadsAmount = numOfThreads;
        commandsAmount = numOfCommands;
        commands = input;
        angles = new AngleType[commandsAmount];
        for (int i = 0; i < commandsAmount; i++)
            angles[i] = new AngleType(commands[i].angle);
        anglesPrefixes = new AngleType[threadsAmount];
        for (int i = 0; i < threadsAmount; i++)
            anglesPrefixes[i] = new AngleType(0);
        coordinatesPrefixes = new CoordinatesType[threadsAmount];
        for (int i = 0; i < threadsAmount; i++)
            coordinatesPrefixes[i] = new CoordinatesType(0, 0);
    }
}
