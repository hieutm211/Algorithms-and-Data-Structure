import java.util.Comparator;

public class Heap<E> {

    private E[] data;
    private int size;
    private Comparator<E> comparator;

    public Heap() {
        this(null);
    }

    public Heap(int capacity) {
        this(capacity, null);
    }

    @SuppressWarnings("unchecked")
    public Heap(Comparator<E> comparator) {
        data = (E[]) new Object[11];
        size = 1;
        this.comparator = comparator;
    }

    @SuppressWarnings("unchecked")
    public Heap(int capacity, Comparator<E> comparator) {
        data = (E[]) new Object[capacity+1];
        size = 1;
        this.comparator = comparator;
    }

    public void add(E element) {
        if (size == data.length) {
            addCapacity();
        }

        data[size] = element;
        swim(size);
        size++;
    }

    public E poll() {
        E result = data[1];
        exchange(1, --size);
        sink(1);
        return result;
    }

    public E peek() {
        return data[1];
    }

    private void swim(int i) {
        int parent = i/2;
        while (parent != 0 && less(data[i], data[parent])) {
            exchange(i, parent);
            i = parent;
            parent = i/2;
        }
    }

    private void sink(int i) {
        int child = i*2;
        while (child < size) {
            if (child+1 < size && less(data[child+1], data[child])) {
                child++;
            }
            if (less(data[child], data[i])) {
                exchange(i, child);
                i = child;
                child = i*2;
            } else {
                break;
            }
        }
    }

    public void addCapacity() {
        addCapacity(data.length);
    }

    @SuppressWarnings("unchecked")
    public void addCapacity(int delta) {
        E[] newData = (E[]) new Object[data.length+delta];
        System.arraycopy(data, 0, newData, 0, data.length);
        data = newData;
    }

    private void exchange(int i, int j) {
        E temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    private boolean less(E a, E b) {
        if (comparator == null) {
            Comparable<? super E> keyA = (Comparable<? super E>) a;
            return keyA.compareTo(b) < 0;
        }
        return comparator.compare(a, b) < 0;
    }

    public boolean isEmpty() {
        return size == 1;
    }

    public int size() {
        return size-1;
    }

    public int capacity() {
        return data.length-1;
    }
}
