package com.company.algorithm9;

import com.company.parallel_scan.ValueType;

public class IntBracketType implements ValueType<IntBracketType> {
    int value;

    public IntBracketType(int value) {
        this.value = value;
    }

    @Override
    public IntBracketType add(IntBracketType a) {
        return new IntBracketType(value + a.value);
    }
}
