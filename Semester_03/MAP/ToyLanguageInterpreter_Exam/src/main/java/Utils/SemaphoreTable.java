package Utils;

import javafx.util.Pair;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;
import Exceptions.MyException;

public class SemaphoreTable implements ISemaphoreTable {
    private Map<Integer, Pair<Integer, List<Integer>>> table;
    private int freeLocation;
    private final ReentrantLock lock;

    public SemaphoreTable() {
        this.table = new HashMap<>();
        this.freeLocation = 1;
        this.lock = new ReentrantLock();
    }

    @Override
    public int allocate(Pair<Integer, List<Integer>> value) throws MyException {
        lock.lock();
        try {
            table.put(freeLocation, value);
            return freeLocation++;
        } finally {
            lock.unlock();
        }
    }

    @Override
    public Pair<Integer, List<Integer>> lookUp(int key) throws MyException {
        lock.lock();
        try {
            if (!isDefined(key))
                throw new MyException("Semaphore index not found: " + key);
            return table.get(key);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public void update(int key, Pair<Integer, List<Integer>> value) throws MyException {
        lock.lock();
        try {
            if (!isDefined(key))
                throw new MyException("Semaphore index not found: " + key);
            table.put(key, value);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public boolean isDefined(int key) {
        lock.lock();
        try {
            return table.containsKey(key);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public Map<Integer, Pair<Integer, List<Integer>>> getContent() {
        lock.lock();
        try {
            return table;
        } finally {
            lock.unlock();
        }
    }

    @Override
    public void setContent(Map<Integer, Pair<Integer, List<Integer>>> newMap) {
        lock.lock();
        try {
            table = newMap;
        } finally {
            lock.unlock();
        }
    }

    @Override
    public String toString() {
        lock.lock();
        try {
            StringBuilder sb = new StringBuilder();
            for (Map.Entry<Integer, Pair<Integer, List<Integer>>> entry : table.entrySet()) {
                sb.append(entry.getKey())
                  .append("->")
                  .append("(")
                  .append(entry.getValue().getKey())
                  .append(",")
                  .append(entry.getValue().getValue())
                  .append(")\n");
            }
            return sb.toString();
        } finally {
            lock.unlock();
        }
    }
} 