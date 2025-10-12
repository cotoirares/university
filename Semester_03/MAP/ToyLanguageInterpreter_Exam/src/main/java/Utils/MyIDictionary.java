package Utils;

import java.util.List;

public interface MyIDictionary<K, V> {
    void put(K key, V value);
    void update(K key, V value);
    V lookUp(K key);
    boolean isDefined(K key);
    List<V> getValues();
    MyIDictionary<K, V> deepCopy();
}
