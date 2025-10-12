package Utils;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class MyDictionary<K, V> implements MyIDictionary<K, V> {
    private Map<K, V> map;

    public MyDictionary() {
        this.map = new HashMap<K, V>();
    }

    @Override
    public void put(K key, V value) {
        this.map.put(key, value);
    }

    @Override
    public void update(K key, V value) {
        this.put(key, value);
    }

    @Override
    public V lookUp(K key) {
        return this.map.get(key);
    }

    @Override
    public boolean isDefined(K key) {
        return this.map.get(key) != null;
    }

    @Override
    public String toString() {
        return this.map.toString();
    }
    @Override
    public List<V> getValues() {
        return new LinkedList<V>(map.values());
    }

    @Override
    public MyIDictionary<K, V> deepCopy() {
        MyDictionary<K, V> copy = new MyDictionary<>();
        copy.map = new HashMap<>(map);
        return copy;
    }
    public Map<K, V> getDict() {
        return map;
    }
}
