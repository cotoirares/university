package Model.Expression;

import Exceptions.DivisionException;
import Exceptions.ExpressionException;
import Exceptions.InterpreterException;
import Exceptions.MyException;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;
import Utils.MyIDictionary;
import Utils.MyIHeap;

public class ArithmeticExpression implements IExpression {
    private IExpression exp1;
    private IExpression exp2;
    private String operation;

    public ArithmeticExpression(String operation, IExpression exp1, IExpression exp2) {
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
        if (v1.getType().equals(new IntType())) {
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int val1, val2;
                val1 = i1.getVal();
                val2 = i2.getVal();
                if (operation.equals("+")) return new IntValue(val1 + val2);
                if (operation.equals("-")) return new IntValue(val1 - val2);
                if (operation.equals("*")) return new IntValue(val1 * val2);
                if (operation.equals("/")) {
                    if (val2 == 0) throw new DivisionException("division by zero");
                    return new IntValue(val1 / val2);
                }
                throw new ExpressionException("invalid operation");
            } else throw new InterpreterException("the operands are not integers");
        } else {
            throw new InterpreterException("the operands are not integers");
        }
    }

    @Override
    public IExpression deepCopy(){
        return new ArithmeticExpression (operation, exp1.deepCopy(), exp2.deepCopy());
    }

    public String toString(){
        return exp1.toString() + " " + operation + " " + exp2.toString();
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws ExpressionException {
        Type type1, type2;
        type1 = exp1.typecheck(typeEnv);
        type2 = exp2.typecheck(typeEnv);
        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
            } else {
                throw new ExpressionException("Arithmetic exp: second operand is not an integer");
            }
        } else {
            throw new ExpressionException("Arithmetic exp: first operand is not an integer");
        }
    }
}
