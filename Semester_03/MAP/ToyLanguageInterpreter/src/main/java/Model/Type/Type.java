package Model.Type;

import Model.Value.Value;

public interface Type {
    Type deepCopy();
    Value defaultValue();
}
