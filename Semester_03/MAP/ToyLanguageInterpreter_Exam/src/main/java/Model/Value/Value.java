package Model.Value;

import Model.Type.Type;

public interface Value {
    Type getType();
    Value deepCopy();
}
