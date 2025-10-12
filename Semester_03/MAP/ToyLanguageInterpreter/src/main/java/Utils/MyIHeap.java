package Utils;

import java.util.List;
import java.util.Map;
import java.util.Set;

import Exceptions.HeapException;
import Model.Value.Value;

public interface MyIHeap<K, V> {
  V get(K key) throws HeapException;
  void put(K key, V value);
  void remove(K key);
  boolean isDefined(K key);
  String toString();
  Map<K, V> getHeap();
  List<V> getValues();
  void setHeap(Map<K, V> dictionary);
  Map<Integer, Value> safeGarbageCollector(Set<Integer> unionSetOfUsedAddr, Map<Integer, Value> heap);
  Integer allocate();
}