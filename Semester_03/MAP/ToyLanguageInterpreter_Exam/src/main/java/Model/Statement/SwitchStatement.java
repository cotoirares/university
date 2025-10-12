package Model.Statement;

import Exceptions.MyException;
import Model.Expression.IExpression;
import Model.Expression.RelationalExpression;
import Model.ProgState;
import Model.Type.Type;
import Utils.MyIDictionary;

public class SwitchStatement implements IStatement {
    private final IExpression exp;
    private final IExpression exp1;
    private final IExpression exp2;
    private final IStatement stmt1;
    private final IStatement stmt2;
    private final IStatement stmt3;

    public SwitchStatement(IExpression exp, IExpression exp1, IStatement stmt1,
                          IExpression exp2, IStatement stmt2, IStatement stmt3) {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.stmt3 = stmt3;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        IStatement convertedStmt = new IfStatement(
            new RelationalExpression("==", exp, exp1),
            stmt1,
            new IfStatement(
                new RelationalExpression("==", exp, exp2),
                stmt2,
                stmt3
            )
        );
        state.getExecStack().push(convertedStmt);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type expType = exp.typecheck(typeEnv);
        Type exp1Type = exp1.typecheck(typeEnv);
        Type exp2Type = exp2.typecheck(typeEnv);

        if (!expType.equals(exp1Type) || !expType.equals(exp2Type))
            throw new MyException("Switch expressions do not have the same type");

        // typecheck
        stmt1.typecheck(typeEnv.deepCopy());
        stmt2.typecheck(typeEnv.deepCopy());
        stmt3.typecheck(typeEnv.deepCopy());

        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new SwitchStatement(exp.deepCopy(), exp1.deepCopy(), stmt1.deepCopy(),
                                 exp2.deepCopy(), stmt2.deepCopy(), stmt3.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("switch(%s) (case %s: %s) (case %s: %s) (default: %s)",
                exp.toString(), exp1.toString(), stmt1.toString(),
                exp2.toString(), stmt2.toString(), stmt3.toString());
    }
} 