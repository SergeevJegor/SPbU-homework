package com.company.algorithm10;

import com.company.parallel_scan.ValueType;

public class AngleType implements ValueType<AngleType> {
    double value;

    public AngleType(double value) {
        this.value = value;
    }

    @Override
    public AngleType add(AngleType c) {
        return new AngleType(this.value + c.value);
    }
}