/*
 * Copyright (c) 2014, Oracle America, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *  * Neither the name of Oracle nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
package com.company;


import com.company.algorithm10.CommandType;
import com.company.algorithm8.PairType;
import com.company.one_threaded.Main;
import org.openjdk.jmh.annotations.*;

import java.util.concurrent.TimeUnit;


@Fork(1)
@Warmup(iterations = 1, time = 5)
@Measurement(iterations = 5, time = 5)
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
public class MyBenchmark {

    @Benchmark
    public void algo3_Single(MyState state) {
        Main.algorithm3(state.ALGO3_SIZE, state.algo3_num1, state.algo3_num2);
    }

    @Benchmark
    public void algo3_1thread(MyState state) {
        com.company.algorithm3.Main.launch(state.ALGO3_SIZE, 1, state.algo3_num1, state.algo3_num2);
    }

    @Benchmark
    public void algo3_2threads(MyState state) {
        com.company.algorithm3.Main.launch(state.ALGO3_SIZE, 2, state.algo3_num1, state.algo3_num2);
    }

    @Benchmark
    public void algo3_4threads(MyState state) {
        com.company.algorithm3.Main.launch(state.ALGO3_SIZE, 4, state.algo3_num1, state.algo3_num2);
    }

    @Benchmark
    public void algo3_8threads(MyState state) {
        com.company.algorithm3.Main.launch(state.ALGO3_SIZE, 8, state.algo3_num1, state.algo3_num2);
    }


    @Benchmark
    public void algo8_Single(MyState state) {
        Main.algorithm8(state.ALGO8_SIZE, state.algo8_pairs);
    }

    @Benchmark
    public void algo8_1thread(MyState state) {
        com.company.algorithm8.Main.launch(1, state.ALGO8_SIZE, state.algo8_pairs);
    }

    @Benchmark
    public void algo8_2threads(MyState state) {
        com.company.algorithm8.Main.launch(2, state.ALGO8_SIZE, state.algo8_pairs);
    }

    @Benchmark
    public void algo8_4threads(MyState state) {
        com.company.algorithm8.Main.launch(4, state.ALGO8_SIZE, state.algo8_pairs);
    }

    @Benchmark
    public void algo8_8threads(MyState state) {
        com.company.algorithm8.Main.launch(8, state.ALGO8_SIZE, state.algo8_pairs);
    }


    @Benchmark
    public void algo9_Single(MyState state) {
        Main.algorithm9(state.algo9_brackets);
    }

    @Benchmark
    public void algo9_1thread(MyState state) {
        com.company.algorithm9.Main.launch(1, state.algo9_brackets);
    }

    @Benchmark
    public void algo9_2threads(MyState state) {
        com.company.algorithm9.Main.launch(2, state.algo9_brackets);
    }

    @Benchmark
    public void algo9_4threads(MyState state) {
        com.company.algorithm9.Main.launch(4, state.algo9_brackets);
    }

    @Benchmark
    public void algo9_8threads(MyState state) {
        com.company.algorithm9.Main.launch(8, state.algo9_brackets);
    }


    @Benchmark
    public void algo10_Single(MyState state) {
        Main.algorithm10(state.ALGO10_SIZE, state.algo10_commands);
    }

    @Benchmark
    public void algo10_1thread(MyState state) {
        com.company.algorithm10.Main.launch(1, state.ALGO10_SIZE, state.algo10_commands);
    }

    @Benchmark
    public void algo10_2threads(MyState state) {
        com.company.algorithm10.Main.launch(2, state.ALGO10_SIZE, state.algo10_commands);
    }

    @Benchmark
    public void algo10_4threads(MyState state) {
        com.company.algorithm10.Main.launch(4, state.ALGO10_SIZE, state.algo10_commands);
    }

    @Benchmark
    public void algo10_8threads(MyState state) {
        com.company.algorithm10.Main.launch(8, state.ALGO10_SIZE, state.algo10_commands);
    }

    @State(Scope.Benchmark)
    public static class MyState {

        final int ALGO3_SIZE = 100000;
        final int ALGO8_SIZE = 10000;
        final int ALGO9_SIZE = 100000;
        final int ALGO10_SIZE = 100000;
        String algo3_num1;
        String algo3_num2;
        PairType[] algo8_pairs;
        String algo9_brackets;
        CommandType[] algo10_commands;

        @Setup(Level.Trial)
        public void doSetup() {
            System.out.print("Setting up");
            // Algo3 setup:
            System.out.print(".");
            StringBuilder num1 = new StringBuilder();
            StringBuilder num2 = new StringBuilder();
            for (int i = 0; i < ALGO3_SIZE; i++) {
                num1.append(i % 10);
                num2.append((i + 3) % 10);
            }
            algo3_num1 = new String(num1);
            algo3_num2 = new String(num2);
            // Algo8 setup:
            System.out.print(".");
            algo8_pairs = new PairType[ALGO8_SIZE];
            for (int i = 0; i < ALGO8_SIZE; i++) {
                algo8_pairs[i] = new PairType(i % 10, i);
            }
            // Algo9 setup:
            System.out.print(".");
            StringBuilder temp = new StringBuilder();
            for (int i = 0; i < ALGO9_SIZE; i++) {
                temp.append(i % 2 == 0 ? "(" : ")");
            }
            algo9_brackets = new String(temp);
            // Algo10 setup:
            System.out.print(".");
            algo10_commands = new CommandType[ALGO10_SIZE];
            for (int i = 0; i < ALGO10_SIZE; i++) {
                algo10_commands[i] = new CommandType((double) i % 360, (double) i % 10);
            }
            System.out.println(".");
        }

        @TearDown(Level.Trial)
        public void doTearDown() {
        }
    }


}