package Utils;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.List;
import java.util.Set;

import Exceptions.HeapException;
import Model.Value.Value;

public class MyHeap<K, V> implements MyIHeap<K, V>{
    private Integer freeAddress;
    private Map<K, V> heap;

    public MyHeap() {
        this.freeAddress = 1;
        this.heap = new HashMap<>();
    }

    @Override
    public V get(K key) throws HeapException {
        if (this.heap.containsKey(key))
            return this.heap.get(key);
        throw new HeapException("Key not found in heap.");
    }

    @Override
    public void put(K key, V value) {
        this.heap.put(key, value);
    }

    @Override
    public boolean isDefined(K key) {
        return this.heap.containsKey(key);
    }

    @Override
    public void remove(K key) {
        this.heap.remove(key);
    }

    @Override
    public String toString() {
        if (this.heap.isEmpty()) {
            return "(Heap is empty!)\n";
    }

    StringBuilder s = new StringBuilder();
        for (K key : this.heap.keySet()) {
            s.append(key.toString()).append(" -> ");
            s.append(this.heap.get(key).toString());
            s.append("\n");
    }
        return s.toString();
    }

    @Override
    public Map<K, V> getHeap() {
        return this.heap;
    }

    @Override
    public List<V> getValues() {
        return new LinkedList<V>(this.heap.values());
    }

    @Override
    public Map<Integer, Value> safeGarbageCollector(Set<Integer> usedAddresses, Map<Integer, Value> heap) {
        Map<Integer, Value> newHeap = new HashMap<Integer, Value>();
        for (Integer key : heap.keySet()) {
        if (usedAddresses.contains(key)) {
            newHeap.put(key, heap.get(key));
         }
        }
        return newHeap;
    }

    @Override
    public void setHeap(Map<K, V> heap) {
        this.heap = heap;
    }

    @Override
    public Integer allocate() {
        return this.freeAddress++;
    }
}
