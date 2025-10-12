package Utils;

import javafx.util.Pair;
import java.util.List;
import java.util.Map;
import Exceptions.MyException;

public interface ISemaphoreTable {
    int allocate(Pair<Integer, List<Integer>> value) throws MyException;
    Pair<Integer, List<Integer>> lookUp(int key) throws MyException;
    void update(int key, Pair<Integer, List<Integer>> value) throws MyException;
    boolean isDefined(int key);
    Map<Integer, Pair<Integer, List<Integer>>> getContent();
    void setContent(Map<Integer, Pair<Integer, List<Integer>>> newMap);
} 