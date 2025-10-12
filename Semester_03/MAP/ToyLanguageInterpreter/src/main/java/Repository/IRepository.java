package Repository;

import Exceptions.MyException;
import Model.ProgState;

import java.util.List;

public interface IRepository {
    void add(ProgState s);
    void logProgState(ProgState state) throws MyException;
    List<ProgState> getProgList();
    void setProgList(List<ProgState> progList);
}
