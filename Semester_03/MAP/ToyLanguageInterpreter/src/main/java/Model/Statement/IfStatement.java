package Model.Statement;

import Exceptions.ExpressionException;
import Exceptions.MyException;
import Exceptions.StatementException;
import Model.Expression.IExpression;
import Model.ProgState;
import Model.Type.BoolType;
import Model.Type.Type;
import Model.Value.BoolValue;
import Model.Value.Value;
import Utils.MyIDictionary;
import Utils.MyIStack;


public class IfStatement implements  IStatement{
    private IExpression exp;
    private IStatement thenS;
    private IStatement elseS;

    public IfStatement(IExpression exp, IStatement thenS, IStatement elseS) {
        this.exp = exp;
        this.thenS = thenS;
        this.elseS = elseS;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        Value val;
        try{
            val = this.exp.evaluate(state.getSymbolTable(), state.getHeap());
        }
        catch (MyException e){
            throw new MyException(e.getMessage());
        }
        if (val.getType().equals(new BoolType())){
            if (((BoolValue)val).getVal()) {
                MyIStack<IStatement> stack = state.getExecStack();
                stack.push(thenS);
            }
            else {
                MyIStack<IStatement> stack = state.getExecStack();
                stack.push(elseS);
            }
        }
        else{
            throw new StatementException("The condition in the if statement is not a boolean");
        }
        return null;
    }


    @Override
    public IStatement deepCopy() {
        return new IfStatement(exp.deepCopy(), thenS.deepCopy(), elseS.deepCopy());
    }

    public String toString() {
        return "if (" + exp.toString() + ") then (" + thenS.toString() + ") else (" + elseS.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        try {
            Type typexp = exp.typecheck(typeEnv);
            if (typexp.equals(new BoolType())) {
                thenS.typecheck(typeEnv.deepCopy());
                elseS.typecheck(typeEnv.deepCopy());
                return typeEnv;
            } else {
                throw new MyException("The If condition has not the type bool");
            }
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        }
    }
}
