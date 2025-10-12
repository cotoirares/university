package Model.Statement;

import Exceptions.*;
import Model.ProgState;
import Model.Type.Type;
import Model.Value.Value;
import Utils.MyIDictionary;

import Model.Expression.IExpression;

public class AssignStatement implements IStatement {
    private String id;
    IExpression expression;

    public AssignStatement(String id, IExpression expression) {
        this.id = id;
        this.expression = expression;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        MyIDictionary<String,Value> SymbolTable = state.getSymbolTable();
        if(SymbolTable.isDefined(id)) {
            Value val = this.expression.evaluate(SymbolTable, state.getHeap());
            Type typeId = (SymbolTable.lookUp(id)).getType();
            if ((val.getType()).equals(typeId)) {
                SymbolTable.update(id, val);
            } else
                throw new InterpreterException("declared type of variable " + id + " and type of the assigned expression do not match.");
        } else throw new StatementException("the used variable " + id + " was not declared before");

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new AssignStatement(id, expression.deepCopy());
    }

    public String toString() {
        return this.id + " = " + this.expression.toString();
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        try {
            Type typevar = typeEnv.lookUp(id);
            Type typexp;
            try {
                typexp = expression.typecheck(typeEnv);
            } catch (ExpressionException e) {
                throw new MyException(e.getMessage());
            }
            if (typevar.equals(typexp)) {
                return typeEnv;
            } else {
                throw new MyException("Assignment: right and left hand side have different types");
            }
        } catch (DictException e) {
            throw new MyException("Variable " + id + " is not defined in type environment");
        }
    }
}
