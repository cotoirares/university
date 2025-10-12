package Model.Statement;

import Exceptions.InterpreterException;
import Exceptions.MyException;
import Model.ProgState;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.Value;
import Utils.MyIDictionary;

public class VarDeclStatement implements IStatement {
    private String id;
    private Type type;

    public VarDeclStatement(String id, Type type) {
        this.id = id;
        this.type = type;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        if (symbolTable.isDefined(id))
            throw new InterpreterException("Variable " + id + " is already defined!");
        symbolTable.put(id, type.defaultValue());
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new VarDeclStatement(id, type.deepCopy());
    }

    public String toString() {
        return this.type.toString() + " " + this.id;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        typeEnv.put(id, type);
        return typeEnv;
    }
}
