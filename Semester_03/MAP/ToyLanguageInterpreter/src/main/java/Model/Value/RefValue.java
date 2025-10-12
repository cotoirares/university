package Model.Value;

import Model.Type.Type;
import Model.Type.RefType;

public class RefValue implements Value{
    private int address;
    private Type locationType;

    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddress() {
        return address;
    }

    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public boolean equals(Object another) {
        if (another instanceof RefValue) {
            return address == ((RefValue) another).getAddress() && locationType.equals(((RefValue) another).getType());
        }
        return false;
    }

    @Override
    public String toString() {
        return "RefValue(" + address + ", " + locationType.toString() + ")";
    }

    @Override
    public Value deepCopy() {
        return new RefValue(address, locationType.deepCopy());
    }
    
}
