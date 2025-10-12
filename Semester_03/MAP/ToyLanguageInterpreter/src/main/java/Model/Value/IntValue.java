package Model.Value;

import Model.Type.IntType;
import Model.Type.Type;

public class IntValue implements Value {
    int value;

    public IntValue(int v) {
        value = v;
    }

    public int getVal() {
        return value;
    }

    public String toString() {
        return String.valueOf(value);
    }

    public Type getType() {
        return new IntType();
    }

    @Override
    public Value deepCopy() {
        return new IntValue(value);
    }
}
