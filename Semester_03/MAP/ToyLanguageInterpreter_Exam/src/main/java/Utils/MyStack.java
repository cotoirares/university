package Utils;
import java.util.*;

public class MyStack<T> implements MyIStack<T> {
    private Stack<T> stack;

    public MyStack() {
        stack = new Stack<T>();
    }

    @Override
    public T pop() {
        return this.stack.pop();
    }

    @Override
    public void push(T v) {
        this.stack.push(v);
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public List<T> getReversed() {
        List<T> reversed = Arrays.asList((T[]) stack.reversed().toArray());
        return reversed;
    }

    public String toString() {
        return this.stack.toString();
    }
}
