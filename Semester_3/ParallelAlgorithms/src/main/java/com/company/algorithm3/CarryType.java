package com.company.algorithm3;

import com.company.parallel_scan.ValueType;

public class CarryType implements ValueType<CarryType> {
    public Carry value;

    public CarryType(Carry val) {
        this.value = val;
    }

    @Override
    public CarryType add(CarryType b) {
        if (b.value != CarryType.Carry.MAYBE)
            return b;
        else
            return this;
    }

    enum Carry {NEVER, MAYBE, CARRY}
}