package com.company.algorithm10;

import com.company.parallel_scan.ValueType;

public class CoordinatesType implements ValueType<CoordinatesType> {
    double x;
    double y;

    public CoordinatesType(double a, double b) {
        this.x = a;
        this.y = b;
    }

    @Override
    public String toString() {
        return "(" + x + "; " + y + ')';
    }

    @Override
    public CoordinatesType add(CoordinatesType c) {
        return new CoordinatesType(this.x + c.x, this.y + c.y);
    }
}
