package Model.Type;

import Model.Value.RefValue;
import Model.Value.Value;

public class RefType implements Type {
    private Type inner;

    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return inner;
    }

    @Override
    public boolean equals(Object other) {
        if (!(other instanceof RefType)) {
            return false;
        }
        RefType otherRef = (RefType) other;
        return inner.equals(otherRef.getInner());
    }

    @Override
    public String toString() {
        return "Ref(" + inner.toString() + ")";
    }

    @Override
    public Type deepCopy() {
        return new RefType(inner.deepCopy());
    }
    
    @Override
    public Value defaultValue() {
        return new RefValue(0, inner);
    }

}
