package Model.Statement;

import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.ProgState;
import Model.Expression.IExpression;
import Model.Type.BoolType;
import Model.Type.Type;
import Model.Value.BoolValue;
import Model.Value.Value;
import Utils.MyIDictionary;

public class WhileStatement implements IStatement{
    private IExpression expression;
    private IStatement statement;

  public WhileStatement(IExpression expression, IStatement statement) {
    this.expression = expression;
    this.statement = statement;
  }

  @Override
  public ProgState execute(ProgState state) throws MyException {
    Value value;
    try {
      value = expression.evaluate(state.getSymbolTable(), state.getHeap());
    } catch (ExpressionException | MyException e) {
      throw new MyException(e.getMessage());
    }
    if (!value.getType().equals(new BoolType())) {
      throw new MyException("Expression is not of type Bool");
    }
    BoolValue boolValue = (BoolValue) value;
    if (boolValue.getVal()) {
      state.getExecStack().push(this);
      state.getExecStack().push(statement);
    }
    return null;
  }

  @Override
  public IStatement deepCopy() {
    return new WhileStatement(expression.deepCopy(), statement.deepCopy());
  }

  @Override
  public String toString() {
    return "WhileStatement(" + expression + ", " + statement + ")";
  }

  @Override
  public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
    try {
      Type typexp = expression.typecheck(typeEnv);
      if (typexp.equals(new BoolType())) {
        statement.typecheck(typeEnv.deepCopy());
        return typeEnv;
      } else {
        throw new MyException("The While condition has not the type bool");
      }
    } catch (ExpressionException e) {
      throw new MyException(e.getMessage());
    }
  }
}
