package Model.Statement;

import Exceptions.MyException;
import Model.ProgState;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.Value;
import Utils.MyIDictionary;
import javafx.util.Pair;

import java.util.List;

public class AcquireStatement implements IStatement {
    private final String var;

    public AcquireStatement(String var) {
        this.var = var;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        Value varValue = state.getSymbolTable().lookUp(var);
        if (varValue == null || !(varValue instanceof IntValue))
            throw new MyException("Variable " + var + " not found or not of type int");

        int foundIndex = ((IntValue)varValue).getVal();
        if (!state.getSemaphoreTable().isDefined(foundIndex))
            throw new MyException("Semaphore index " + foundIndex + " not found");

        Pair<Integer, List<Integer>> semaphoreValue = state.getSemaphoreTable().lookUp(foundIndex);
        int N1 = semaphoreValue.getKey();
        List<Integer> list1 = semaphoreValue.getValue();
        int NL = list1.size();

        if (N1 > NL) {
            if (!list1.contains(state.getId())) {
                list1.add(state.getId());
                state.getSemaphoreTable().update(foundIndex, new Pair<>(N1, list1));
            }
        } else {
            state.getExecStack().push(this);
        }

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type varType = typeEnv.lookUp(var);
        if (!varType.equals(new IntType()))
            throw new MyException("Variable " + var + " must be of type int");
        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new AcquireStatement(var);
    }

    @Override
    public String toString() {
        return "acquire(" + var + ")";
    }
} 