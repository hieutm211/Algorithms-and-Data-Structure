import java.util.Iterator;

public class UnorderedST<K, V> {

    public static class Node<K, V> implements Iterator<Node> {
        private K key;
        private V value;
        private Node<K, V> next;

        public Node(K key, V value, Node<K, V> next) {
            this.key = key;
            this.value = value;
            this.next = next;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }

        public void setValue(V value) {
            this.value = value;
        }

        public Node<K, V> getNext() {
            return next;
        }

        public void setNext(Node<K, V> next) {
            this.next = next;
        }

        public boolean hasNext() {
            return this.next != null;
        }

        public Node<K, V> next() {
            return this.next();
        }
    }

    private class KeyIterator<K> implements Iterator {
        Node<K, V> node;

        public KeyIterator(Node<K, V> node) {
            this.node = node;
        }

        public boolean hasNext() {
            return node != null;
        }

        public K next() {
            K value = node.getKey();
            node = node.getNext();
            return value;
        }
    }

    private Node<K, V> root;
    private int size;

    UnorderedST() {
        root = null;
    }

    void put(K key, V value) {
        if (!contains(key)) {
            size++;
            root = new Node<>(key, value, root);
        } else {
            Node<K, V> node = root;

            while (!key.equals(node.getKey())) {
                node = node.getNext();
            }

            node.setValue(value);
        }
    }

    public V get(K key) {
        if (!contains(key)) return null;
        Node<K, V> node = root;
        while (!key.equals(node.getKey())) {
            node = node.getNext();
        }
        return node.getValue();
    }

    public void delete(K key) {
        if (!contains(key)) return;

        if (key.equals(root.getKey())) {
            root = root.getNext();
        } else {
            Node<K, V> node = root;
            while (node.getNext() != null && !key.equals(node.getNext().getKey())) {
                node = node.getNext();
            }
            node.setNext(node.getNext().getNext());
        }

        size--;
    }

    public boolean contains(K key) {
        Node<K, V> node = root;
        while (node != null && !key.equals(node.getKey())) {
            node = node.getNext();
        }
        return node != null;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public int size() {
        return size;
    }

    public Iterable<K> keyIterator() {
        return new Iterable<>() {
            public Iterator<K> iterator() {
                return new KeyIterator<K>(root);
            }
        };
    }

    public void print() {
        for (K key : keyIterator()) {
            System.out.print(key + " ");
        }
        System.out.println();
    }
}
