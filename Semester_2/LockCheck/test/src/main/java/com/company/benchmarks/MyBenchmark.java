package com.company.benchmarks;

import org.openjdk.jmh.annotations.Benchmark;


public class MyBenchmark {

    @Benchmark
    public void testTas() {
        Main.tasTest();
    }

    @Benchmark
    public void testTtas() {
        Main.ttasTest();
    }

}
