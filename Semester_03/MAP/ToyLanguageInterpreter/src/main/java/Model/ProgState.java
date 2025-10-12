package Model;

import Exceptions.MyException;
import Exceptions.StackException;
import Model.Value.StringValue;
import Utils.MyIDictionary;
import Utils.MyIList;
import Utils.MyIStack;
import Utils.MyIHeap;
import Model.Statement.IStatement;
import Model.Value.Value;
import Model.Value.RefValue;

import java.io.BufferedReader;
import java.util.HashSet;
import java.util.Set;

public class ProgState {
    private MyIDictionary<String, Value> symbolTable;
    private MyIStack<IStatement> execStack;
    private MyIList<Value> output;
    private IStatement originalProgram;
    private MyIDictionary <StringValue, BufferedReader> fileTable;
    private MyIHeap<Integer, Value> heap;

    private static int nextId = 0;
    private final int id;
    private boolean isNotCompleted;

    public boolean isNotCompleted() {
        return isNotCompleted;
    }

    public void setNotCompleted(boolean isNotCompleted) {
        this.isNotCompleted = isNotCompleted;
    }

    public MyIDictionary<String, Value> getSymbolTable() {
        return symbolTable;
    }

    public MyIStack<IStatement> getExecStack() {
        return execStack;
    }

    public MyIList<Value> getOutput() {
        return output;
    }

    public IStatement getOriginalProgram() {
        return originalProgram;
    }

    public MyIDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public MyIHeap<Integer, Value> getHeap() {
        return heap;
    }

    private static synchronized int getNextId() {
        return nextId++;
    }

    public ProgState(MyIStack<IStatement> execStack, MyIDictionary<String, Value> symbolTable, MyIList<Value> output, IStatement program, MyIDictionary<StringValue, BufferedReader> fileTable, MyIHeap<Integer, Value> heap) {
        this.id = getNextId();
        this.execStack = execStack;
        this.symbolTable = symbolTable;
        this.output = output;
        this.originalProgram = program.deepCopy();
        this.fileTable = fileTable;
        this.heap = heap;
        this.isNotCompleted = true;
        this.execStack.push(program);
    }

    @Override
    public String toString() {
        return "ID: " + this.id + "\nExeStack: " + this.execStack.getReversed() + "\nSymbolTable: " + this.symbolTable.toString() + "\nOutput: " + this.output.toString() + "\n" + "FileTable: " + this.fileTable.toString() + "\n" + "Heap: " + this.heap.toString() + "\n";
    }

    public Set<Integer> getUsedAddresses() {
        Set<Integer> usedAddresses = new HashSet<>();
        for (Value value : this.symbolTable.getValues()) {
          if (value instanceof RefValue) {
            usedAddresses.add(((RefValue) value).getAddress());
          }
        }   
    
        for (Value value : this.heap.getValues()) {
            if (value instanceof RefValue) {
                usedAddresses.add(((RefValue) value).getAddress());
            }
        }
        return usedAddresses;
      }
    public ProgState oneStep() throws MyException {
        if (execStack.isEmpty()) {
            this.isNotCompleted = false;
            return null;
        }
        IStatement createStatement;
        try {
            createStatement = execStack.pop();
        } catch (StackException e) {
            throw new MyException("ProgState stack is empty");
        }
        return createStatement.execute(this);
    }

    public int getId() {
        return id;
    }
}
