package com.company.algorithm10;

import com.company.parallel_scan.ValueType;

public class CommandType implements ValueType<CommandType> {
    double angle;
    double length;

    public CommandType(double angle, double length) {
        this.angle = angle;
        this.length = length;
    }

    @Override
    public CommandType add(CommandType c) {
        return new CommandType(this.angle + c.angle, this.length);
    }
}
