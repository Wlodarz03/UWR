package structures;

import java.util.NoSuchElementException;

public class OrderedList<T extends Comparable<T>> implements OrderedSequence<T>, Iterable<T>  {
    private Node<T> head;
    private int count;

    public OrderedList() {
        this.head = null;
        this.count = 0;
    }

    // klasa Node
    private class Node<T extends Comparable<T>> {
        private T data;
        private Node<T> next;

        Node(T data) {
            if (data == null) throw new NullPointerException("Wartosc null w node");
            this.data = data;
        }
    
        public void setNext(Node<T> next) {
            this.next = next;
        }
    
        public int compareTo(T other) {
            return data.compareTo(other);
        }
    
        public boolean equalsData(T other) {
            return data.equals(other);
        }
    }

    @Override
    public void insert(T el){
        if (el == null) throw new NullPointerException();

        Node<T> newNode = new Node<>(el);
        if (head == null || head.compareTo(el) > 0){
            newNode.setNext(head);
            head = newNode;
        }
        else{
            Node<T> current = head;
            while (current.next != null && current.next.compareTo(el) < 0){
                current = current.next;
            }
            if (current.next != null && current.next.equalsData(el)) {
                return; // jezeli ten element juz jest to nic nie insertuje
            }
            newNode.setNext(current.next);
            current.setNext(newNode);
        }
        count++;
    }

    @Override
    public void remove(T el){
        if (head == null || el == null) throw new NullPointerException();

        if (head.equalsData(el)) {
            head = head.next;
            count--;
            return;
        }

        Node<T> current = head;
        while (current.next != null && !current.next.equalsData(el)) {
            current = current.next;
        }

        if (current.next == null) throw new NoSuchElementException("Nie ma takiego elementu");

        current.setNext(current.next.next);
        count--;
    }

    @Override
    public T min() {
        if (head == null) throw new NoSuchElementException("Pusta lista");
        return head.data;
    }

    @Override
    public T max() {
        if (head == null) throw new NoSuchElementException("Pusta lista");
        Node<T> current = head;
        while (current.next != null) {
            current = current.next;
        }
        return current.data;
    }

    @Override
    public boolean search(T el) {
        if (el == null) return false;
        Node<T> current = head;
        while (current != null) {
            if (current.equalsData(el)) return true;
            current = current.next;
        }
        return false;
    }

    @Override
    public T at(int pos) {
        if (pos < 0 || pos >= count) throw new IndexOutOfBoundsException("Nie ma takiej pozycji");
        Node<T> current = head;
        for (int i = 0; i < pos; i++) {
            current = current.next;
        }
        return current.data;
    }

    @Override
    public int index(T el) {
        Node<T> current = head;
        int index = 0;
        while (current != null) {
            if (current.equalsData(el)) return index;
            current = current.next;
            index++;
        }
        return -1; // nie ma takiego elementu
    }

    @Override
    public int size() {
        return count;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        Node<T> current = head;
        while (current != null) {
            sb.append(current.data);
            if (current.next != null) sb.append(", ");
            current = current.next;
        }
        sb.append("]");
        return sb.toString();
    }

    @Override
    public java.util.Iterator<T> iterator() {
        return new OrderedListIterator();
    }

    // klasa iteratora
    private class OrderedListIterator implements java.util.Iterator<T> {
        private Node<T> current = head;
        private Node<T> lastAccessed = null;

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public T next() {
            if (!hasNext()) throw new NoSuchElementException();
            lastAccessed = current;
            T data = current.data;
            current = current.next;
            return data;
        }

        @Override
        public void remove() {
            if (lastAccessed == null) throw new IllegalStateException("Nie wywolano next() przed remove()");
            OrderedList.this.remove(lastAccessed.data);
            lastAccessed = null;
        }
    }
}
