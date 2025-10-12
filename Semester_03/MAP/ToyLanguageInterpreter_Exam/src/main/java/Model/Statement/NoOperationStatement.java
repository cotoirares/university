package Model.Statement;

import Exceptions.MyException;
import Model.ProgState;
import Model.Type.Type;
import Utils.MyIDictionary;

public class NoOperationStatement implements IStatement{
    @Override
    public ProgState execute(ProgState state) {
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new NoOperationStatement();
    }

    @Override
    public String toString() {
        return "No Operation";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }
}
