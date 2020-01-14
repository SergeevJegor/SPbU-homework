package com.company.one_threaded;

import com.company.algorithm10.CommandType;
import com.company.algorithm10.CoordinatesType;
import com.company.algorithm8.PairType;

import static java.lang.System.exit;

public class Main {
    public static void algorithm3(int numberSize, String num1Str, String num2Str) {
        int[] num1 = new int[numberSize];
        int[] num2 = new int[numberSize];
        int[] result = new int[numberSize];
        for (int i = 0; i < numberSize; i++) {
            num1[i] = num1Str.charAt(numberSize - i - 1) - '0';
            num2[i] = num2Str.charAt(numberSize - i - 1) - '0';
        }
        int carry = 0;
        for (int i = 0; i < numberSize; i++) {
            int sum = (num1[i] + num2[i] + carry);
            result[i] = sum % 10;
            carry = sum / 10;
        }
    }

    public static void algorithm8(int numOfPairs, PairType[] input) {
        int result = 0;
        for (int i = 0; i < numOfPairs; i++)
            result = result * input[i].a + input[i].b;
    }

    public static void algorithm9(String input) {
        int len = input.length();
        int temp = 0;
        for (int i = 0; i < len; i++) {
            temp += input.charAt(i) == '(' ? 1 : -1;
            if (temp < 0) {
                System.out.println("Wrong bracket. Abort");
                exit(1);
            }
        }
        if (temp != 0) {
            System.out.println("Wrong bracket. Abort");
            exit(1);
        }
    }

    public static void algorithm10(int numOfCommands, CommandType[] input) {
        CoordinatesType c = new CoordinatesType(0, 0);
        double angle = 0;
        for (int i = 0; i < numOfCommands; i++) {
            angle += input[i].angle;
            c = c.add(new CoordinatesType(Math.cos(Math.toRadians(angle)) * input[i].length,
                    Math.sin(Math.toRadians(angle)) * input[i].length));
        }
    }
}
