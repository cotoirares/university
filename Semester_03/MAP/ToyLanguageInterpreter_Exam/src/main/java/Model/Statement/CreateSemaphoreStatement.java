package Model.Statement;

import Exceptions.MyException;
import Model.Expression.IExpression;
import Model.ProgState;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;
import Utils.MyIDictionary;
import javafx.util.Pair;

import java.util.ArrayList;

public class CreateSemaphoreStatement implements IStatement {
    private final String var;
    private final IExpression expression;

    public CreateSemaphoreStatement(String var, IExpression expression) {
        this.var = var;
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        Value expValue = expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!(expValue instanceof IntValue))
            throw new MyException("Expression must evaluate to integer");

        IntValue number = (IntValue) expValue;
        int newFreeLocation = state.getSemaphoreTable().allocate(new Pair<>(number.getVal(), new ArrayList<>()));
        
        if (!state.getSymbolTable().isDefined(var))
            throw new MyException("Variable " + var + " not defined");
        
        state.getSymbolTable().update(var, new IntValue(newFreeLocation));
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type varType = typeEnv.lookUp(var);
        Type expType = expression.typecheck(typeEnv);
        
        if (!varType.equals(new IntType()))
            throw new MyException("Variable must be of type int");
        if (!expType.equals(new IntType()))
            throw new MyException("Expression must evaluate to int");
        
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new CreateSemaphoreStatement(var, expression.deepCopy());
    }

    @Override
    public String toString() {
        return "createSemaphore(" + var + ", " + expression.toString() + ")";
    }
} 