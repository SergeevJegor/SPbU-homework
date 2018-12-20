package com.company.algorithm8;

import com.company.parallel_scan.ValueType;

public class PairType implements ValueType<PairType> {
    int a;
    int b;

    public PairType(int a, int b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public PairType add(PairType p) {
        PairType tmp = new PairType(0, 0);
        tmp.a = this.a * p.a;
        tmp.b = p.a * this.b + p.b;
        return tmp;
    }
}
