package structures;

public interface OrderedSequence<T extends Comparable<T>> {
    void insert(T el);
    void remove(T el);
    T min();
    T max();
    boolean search(T el);
    T at(int pos);
    int index(T el);
    int size();
}
