package Model.Statement;

import Exceptions.DictException;
import Exceptions.ExpressionException;
import Exceptions.MyException;
import Model.Expression.IExpression;
import Model.ProgState;
import Model.Type.IntType;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.StringValue;
import Model.Value.Value;
import Utils.MyIDictionary;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStatement {
   private IExpression exp;
   private String varName;

    public ReadFile(IExpression exp, String varName) {
        this.exp = exp;
        this.varName = varName;
    }

    @Override
    public String toString() {
        return "readFile(" + exp.toString() + ", " + varName + ")";
    }

    @Override
    public IStatement deepCopy() {
        return new ReadFile(exp.deepCopy(), varName);
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        if (!state.getSymbolTable().isDefined(varName)){
            throw new MyException("The variable is not declared");
        }

        Value varValue;
        try{
            varValue = state.getSymbolTable().lookUp(varName);
        }
        catch (MyException e){
            throw new MyException(e.getMessage());
        }
        if (!varValue.getType().equals(new IntType())){
            throw new MyException("The variable is not an integer");
        }

        Value fileNameValue;
        try{
            fileNameValue = exp.evaluate(state.getSymbolTable(), state.getHeap());
        }
        catch (MyException e){
            throw new MyException(e.getMessage());
        }
        if (!fileNameValue.getType().equals(new StringType())){
            throw new MyException("The file name is not a string");
        }
        StringValue fileName = (StringValue) fileNameValue;
        BufferedReader bufferedReader;
        try{
            bufferedReader = state.getFileTable().lookUp(fileName);
        }
        catch (DictException e){
            throw new MyException(e.getMessage());
        }
        if (bufferedReader == null){
            throw new MyException("The file is not opened");
        }

        try{
            String line = bufferedReader.readLine();
            IntValue val;
            if (line == null) {
                val = new IntValue(0);
            }
            else{
                try{
                    val = new IntValue(Integer.parseInt(line));
                }
                catch (NumberFormatException e){
                    throw new MyException("Invalid integer format in file");
                }
            }
            try{
                state.getSymbolTable().update(varName, val);
            }
            catch (DictException e){
                throw new MyException(e.getMessage());
            }
        }
        catch (IOException e){
            throw new MyException(e.getMessage());
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp;
        try {
            typexp = exp.typecheck(typeEnv);
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        }
        if (!typexp.equals(new StringType())) {
            throw new MyException("Expression is not a string");
        }
        return typeEnv;
    }
}
