package Model.Statement;

import Exceptions.MyException;
import Model.ProgState;
import Model.Statement.IStatement;
import Model.Type.Type;
import Utils.MyIDictionary;
import Utils.MyStack;

public class ForkStatement implements IStatement {
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgState execute(ProgState currentPrg) throws MyException {
        return new ProgState(
                new MyStack<>(),
                currentPrg.getSymbolTable().deepCopy(),
                currentPrg.getOutput(),
                statement,
                currentPrg.getFileTable(),
                currentPrg.getHeap());
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(statement.deepCopy());
    }

    @Override
    public String toString() {
        return "Fork(" + statement.toString() + ")";
    }
    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        statement.typecheck(typeEnv.deepCopy());
        return typeEnv;
    }
}