package Model.Value;

import Model.Type.Type;
import Model.Type.StringType;

public class StringValue implements Value{
    private String val;

    public StringValue(String val){
        this.val = val;
    }

    public String getVal() {
        return val;
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public boolean equals(Object another){
        if (another instanceof StringValue && ((StringValue) another).getVal().equals(this.val))
            return true;
        else
            return false;
    }

    @Override
    public String toString() {
        return this.val;
    }

    @Override
    public Value deepCopy() {
        return new StringValue(this.val);
    }
}
