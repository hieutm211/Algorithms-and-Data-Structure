import java.util.Iterator;

public class OrderedST<Key extends Comparable<Key>, Value> {

    public static class Node<Key extends Comparable<Key>, Value> {
        private Key key;
        private Value value;

        //Create a node
        public Node(Key key, Value value) {
            this.key = key;
            this.value = value;
        }

        //key of node
        public Key getKey() {
            return key;
        }

        //value of node
        public Value getValue() {
            return value;
        }

        //set value of node
        public void setValue(Value value) {
            this.value = value;
        }
    }

    private class STItr implements Iterator<Key> {
        private int currentIndex;
        private int end;

        public STItr() {
            currentIndex = 0;
            end = size;
        }

        public STItr(int begin, int end) {
            this.currentIndex = begin;
            this.end = end;
        }

        public boolean hasNext() {
            return currentIndex < end;
        }

        public Key next() {
            Key temp = get(currentIndex).getKey();
            currentIndex++;
            return temp;
        }
    }

    private Object[] table;
    private int size;

    //create an ordered symbol table
    public OrderedST() {
        table = new Object[10];
        size = 0;
    }

    //put key-value pair into the table (remove key from table if value is null)
    public void put(Key key, Value value) {
        if (value == null) {
            delete(key);
            return;
        }

        int index = rank(key);
        Node<Key, Value> newNode = new Node<>(key, value);

        if (index != size && select(index).equals(key)) {
            table[index] = newNode;
        } else {
            put(index, newNode);
        }
    }

    //value paired with key (null if key is absent)
    @SuppressWarnings("unchecked")
    public Value get(Key key) {
        int index = find(key);

        if (index == -1) {
            return null;
        } else {
            return get(index).getValue();
        }
    }

    //remove key (and its value) from table
    @SuppressWarnings("unchecked")
    public void delete(Key key) {
        int index = find(key);

        if (index != -1) {
            delete(index);
        }
    }

    //is there a value paired with key?
    public boolean contains(Key key) {
        return find(key) != -1;
    }

    //is the table empty?
    public boolean isEmpty() {
        return size == 0;
    }

    //number of key-value pairs
    public int size() {
        return size;
    }

    //smallest key
    public Key min() {
        if (size == 0) return null;
        return select(0);
    }

    //largest key
    public Key max() {
        if (size == 0) return null;
        return select(size-1);
    }

    //largest key less than or equal to key
    public Key floor(Key key) {
        int index = floorIndex(key);
        if (index == -1) return null;
        else return select(index);
    }

    //smallest key greater than or equal to key
    public Key ceiling(Key key) {
        int index = ceilingIndex(key);
        if (index == size) return null;
        return select(index);
    }

    //number of keys less than key
    public int rank(Key key) {
        return ceilingIndex(key);
    }

    //key of rank k
    @SuppressWarnings("unchecked")
    public Key select(int k) {
        return get(k).getKey();
    }

    //delete smallest key
    public void deleteMin() {
        delete(0);
    }

    //delete largest key
    public void deleteMax() {
        delete(size-1);
    }

    //number of keys in [lo..hi]
    public int size(Key lo, Key hi) {
        if (hi.compareTo(lo) < 0) return 0;
        if (size == 0) return 0;
        if (hi.compareTo(select(0)) < 0) return 0;
        if (select(size-1).compareTo(lo) < 0) return 0;

        return floorIndex(hi) - ceilingIndex(lo) + 1;
    }

    //keys in [lo..hi], in sorted order
    public Iterable<Key> keys(Key lo, Key hi) {
        return new Iterable<Key>() {
            public Iterator<Key> iterator() {
                if (size == 0) return new STItr();
                if (hi.compareTo(lo) < 0 || hi.compareTo(select(0)) < 0 || select(size-1).compareTo(lo) < 0) {
                    return new STItr(0, 0);
                }
                return new STItr(ceilingIndex(lo), floorIndex(hi)+1);
            }
        };
    }

    //all keys in the table, in sorted order
    public Iterable<Key> keys() {
        return new Iterable<Key>() {
            public Iterator<Key> iterator() {
                return new STItr();
            }
        };
    }

    private void increaseCapacity() {
        int newSize;
        if (table.length <= 50000) {
            newSize = size+size;
        } else {
            newSize = size + (size>>1);
        }

        Object[] newTable = new Object[newSize];
        System.arraycopy(table, 0, newTable, 0, table.length);

        table = newTable;
    }

    //delete element at index
    private void delete(int index) {
        if (index >= size) return;
        for (int i = index; i < size-1; i++) {
            table[i] = table[i+1];
        }
        size--;
    }

    //put a node in index
    private void put(int index, Node<Key, Value> node) {
        size++;
        for (int i = size-1; i >= index+1; i--) {
            table[i] = table[i-1];
        }
        table[index] = node;
    }

    //index of key (-1 if not found).
    private int find(Key key) {
        int lo = 0, hi = size-1;
        while (lo <= hi) {
            int mid = lo + (hi-lo)/2;

            Key midKey = select(mid);

            if (key.compareTo(midKey) < 0) {
                hi = mid-1;
            } else if (key.compareTo(midKey) > 0) {
                lo = mid+1;
            } else {
                return mid;
            }
        }

        return -1;
    }

    //node at index
    @SuppressWarnings("unchecked")
    private Node<Key, Value> get(int index) {
        return (Node<Key, Value>) table[index];
    }

    //index of floor key (-1 if key < all keys)
    private int floorIndex(Key key) {
        int lo = 0, hi = size-1, answer = -1;
        while (lo <= hi) {
            int mid = lo + (hi-lo)/2;

            Key midKey = select(mid);

            if (midKey.compareTo(key) <= 0) {
                answer = mid;
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }

        return answer;
    }

    //index of ceil key (return size if all keys < key)
    private int ceilingIndex(Key key) {
        int lo = 0, hi = size-1, answer = size;
        while (lo <= hi) {
            int mid = lo + (hi-lo)/2;

            Key midKey = select(mid);

            if (midKey.compareTo(key) >= 0) {
                answer = mid;
                hi = mid-1;
            } else {
                lo = mid+1;
            }
        }

        return answer;
    }

    public void print() {
        System.out.print("ST: ");
        for (int i = 0; i < size; i++) {
            Node<Key, Value> node = get(i);
            System.out.print("<" + node.getKey() + " " + node.getValue() + ">, ");
        }
        System.out.println();
    }
}
