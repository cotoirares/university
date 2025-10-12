package Model.Statement;

import Exceptions.DictException;
import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.ProgState;
import Model.Expression.IExpression;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.Value;
import Model.Value.RefValue;
import Utils.MyIDictionary;

public class WriteHeapStatement implements IStatement{
    private String varName;
    private IExpression expression;

    public WriteHeapStatement(String varName, IExpression expression) {
        this.varName = varName;
        this.expression = expression;
  }

  @Override
  public ProgState execute(ProgState prg) throws MyException {
    if (!prg.getSymbolTable().isDefined(varName)) {
      throw new MyException("Variable " + varName + " was not declared");
    }

    Value varValue;
    try {
      varValue = prg.getSymbolTable().lookUp(varName);
    } catch (DictException e) {
      throw new MyException(e.getMessage());
    }
    if (!(varValue instanceof RefValue)) {
      throw new MyException("Variable " + varName + " is not of RefType");
    }

    RefValue refValue = (RefValue) varValue;
    Integer address = refValue.getAddress();

    if (!prg.getHeap().isDefined(address)) {
      throw new MyException("Address " + address + " is not allocated on the heap");
    }

    Value value;
    try {
      value = expression.evaluate(prg.getSymbolTable(), prg.getHeap());
    } catch (ExpressionException | MyException e) {
      throw new MyException(e.getMessage());
    }
    if (!value.getType().equals(((RefType) refValue.getType()).getInner())) {
      throw new MyException("Type of expression and type of variable do not match");
    }

    prg.getHeap().put(address, value);
    return null;
  }

  @Override
  public IStatement deepCopy() {
    return new WriteHeapStatement(varName, expression.deepCopy());
  }

  @Override
  public String toString() {
    return "WriteHeapStmt(" + varName + ", " + expression + ")";
  }

  @Override
  public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
    try {
      Type typevar = typeEnv.lookUp(varName);
      Type typexp = expression.typecheck(typeEnv);
      if (typexp.equals(new RefType(typexp).getInner())) {
        RefType reft = (RefType) typevar;
        if (typexp.equals(reft.getInner())) {
          return typeEnv;
        } else {
          throw new MyException("WriteHeapStmt: right and left hand side have different types");
        }
      } else {
        throw new MyException("WriteHeapStmt: " + varName + " is not of RefType");
      }
    } catch (DictException e) {
      throw new MyException("Variable " + varName + " is not defined in type environment");
    } catch (ExpressionException e) {
      throw new MyException(e.getMessage());
    }
  }
}
