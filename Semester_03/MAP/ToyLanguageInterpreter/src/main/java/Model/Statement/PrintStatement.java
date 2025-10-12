package Model.Statement;

import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.Expression.IExpression;
import Model.ProgState;
import Model.Type.Type;
import Utils.MyIDictionary;

public class PrintStatement implements IStatement {
    private IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        state.getOutput().add(expression.evaluate(state.getSymbolTable(), state.getHeap()));
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(expression.deepCopy());
    }

    public String toString() {
        return "print(" + expression.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        try {
            expression.typecheck(typeEnv);
            return typeEnv;
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        }
    }
}
