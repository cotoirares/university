package Model.Expression;

import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.Type.BoolType;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.BoolValue;
import Model.Value.IntValue;
import Model.Value.Value;
import Utils.MyIDictionary;
import Utils.MyIHeap;

public class RelationalExpression implements IExpression{
    private IExpression exp1;
    private IExpression exp2;
    private String operation;

    public RelationalExpression(String operation, IExpression exp1, IExpression exp2) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.operation = operation;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symTable, MyIHeap<Integer, Value> heap)
    throws MyException, ExpressionException {
        Value v1, v2;
        v1 = exp1.evaluate(symTable, heap);
        v2 = exp2.evaluate(symTable, heap);

        if (v1.getType().equals(new IntType()) && v2.getType().equals(new IntType())){
            IntValue i1 = (IntValue) v1;
            IntValue i2 = (IntValue) v2;
            int nr1, nr2;
            nr1 = i1.getVal();
            nr2 = i2.getVal();
            if (operation.equals("<")) return new BoolValue(nr1 < nr2);
            if (operation.equals("<=")) return new BoolValue(nr1 <= nr2);
            if (operation.equals("==")) return new BoolValue(nr1 == nr2);
            if (operation.equals("!=")) return new BoolValue(nr1 != nr2);
            if (operation.equals(">")) return new BoolValue(nr1 > nr2);
            if (operation.equals(">=")) return new BoolValue(nr1 >= nr2);
            throw new ExpressionException("Invalid operation");
        }
        else throw new ExpressionException("The operands are not integers");
    }
    @Override
    public IExpression deepCopy(){
        return new RelationalExpression(operation, exp1.deepCopy(), exp2.deepCopy());
    }

    public String toString(){
        return exp1.toString() + operation + exp2.toString();
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws ExpressionException {
        Type type1, type2;
        type1 = exp1.typecheck(typeEnv);
        type2 = exp2.typecheck(typeEnv);
        if (type1.equals(new IntType()) && type2.equals(new IntType())) {
            return new BoolType();
        } else {
            throw new ExpressionException("RelExp: operands are not integers");
        }
    }
}
