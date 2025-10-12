package Model.Value;

import Model.Type.BoolType;
import Model.Type.Type;

public class BoolValue implements Value{
    private boolean value;

    public BoolValue(boolean v) {
        value = v;
    }

    public boolean getVal() {
        return value;
    }

    public String toString() {
        return String.valueOf(value);
    }

    public Type getType() {
        return new BoolType();
    }

    @Override
    public Value deepCopy() {
        return new BoolValue(value);
    }
}
