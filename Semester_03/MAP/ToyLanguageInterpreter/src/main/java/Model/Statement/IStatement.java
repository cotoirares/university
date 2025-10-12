package Model.Statement;

import Exceptions.MyException;
import Model.ProgState;
import Model.Type.Type;
import Utils.MyIDictionary;

public interface IStatement {
    ProgState execute(ProgState state) throws MyException;
    IStatement deepCopy();
    MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException;
}
