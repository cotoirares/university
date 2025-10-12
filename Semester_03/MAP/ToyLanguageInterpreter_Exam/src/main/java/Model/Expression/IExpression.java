package Model.Expression;

import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.Type.Type;
import Model.Value.Value;
import Utils.MyIDictionary;
import Utils.MyIHeap;

public interface IExpression {
    Value evaluate(MyIDictionary<String,Value> SymbolTable, MyIHeap<Integer, Value> heap) throws MyException, ExpressionException;
    Type typecheck(MyIDictionary<String, Type> typeEnv) throws ExpressionException;
    IExpression deepCopy();
}
