package com.company.algorithm10;

public class Calculator implements Runnable {
    private int from;
    private int to;
    private int threadID;
    private CoordinatesType[] coordinates;
    private CoordinatesType[] prefixes;

    public Calculator(int from, int to, int threadID, CoordinatesType[] coordinates, CoordinatesType[] prefixes) {
        this.from = from;
        this.to = to;
        this.threadID = threadID;
        this.coordinates = coordinates;
        this.prefixes = prefixes;
    }

    @Override
    public void run() {
        CoordinatesType folder = coordinates[from];
        for (int i = from + 1; i < to; i++) {
//            System.out.print(folder + "+" + coordinates[i] + "=");
            folder = folder.add(coordinates[i]);
//            System.out.println(folder);
        }

        prefixes[threadID] = folder;
    }
}
