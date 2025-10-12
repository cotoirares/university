package Model.Expression;

import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.Type.Type;
import Model.Value.Value;
import Utils.MyIDictionary;
import Utils.MyIHeap;

public class ValueExpression implements IExpression {

    private Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symTable, MyIHeap<Integer, Value> heap)
    throws MyException, ExpressionException {
        return value;
    }

    @Override
    public IExpression deepCopy() {
        return new ValueExpression(value.deepCopy());
    }

    public String toString() {
        return this.value.toString();
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws ExpressionException {
        return this.value.getType();
    }
}
