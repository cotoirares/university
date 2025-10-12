package Model.Type;

import Model.Value.Value;
import Model.Value.BoolValue;

public class BoolType implements Type{
    private String type = "bool";

    @Override
    public boolean equals(Object obj) {
        return obj instanceof BoolType;
    }

    @Override
    public String toString() {
        return this.type;
    }

    @Override
    public Type deepCopy() {
        return new BoolType();
    }

    @Override
    public Value defaultValue() {
        return new BoolValue(false);
    }
}
