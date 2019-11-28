import java.util.ArrayList;
import java.util.Iterator;

public class BST_firstImplement<K extends Comparable<K>, V> {
    private Node<K, V> root;
    private int size;

    //node of BST
    private static class Node<K extends Comparable<K>, V> {
        private K key;
        private V value;
        private Node<K, V> parent, left, right;

        public Node(K key, V value) {
            this(key, value, null, null, null);
        }

        public Node(K key, V value, Node<K, V> left, Node<K, V> right) {
            this(key, value, null, left, right);
        }

        public Node(K key, V value, Node<K, V> parent, Node<K, V> left, Node<K, V> right) {
            this.key = key;
            this.value = value;
            this.parent = parent;
            this.left = left;
            this.right = right;
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

        public Node<K, V> getParent() {
            return parent;
        }

        public void setParent(Node<K, V> parent) {
            this.parent = parent;
        }

        public Node<K, V> getLeft() {
            return left;
        }

        public void setLeft(Node<K, V> left) {
            if (left != null) {
                left.setParent(this);
            }
            this.left = left;
        }

        public Node<K, V> getRight() {
            return right;
        }

        public void setRight(Node<K, V> right) {
            if (right != null) {
                right.setParent(this);
            }
            this.right = right;
        }
    }

    public class KeyItr implements Iterator<K> {
        private Object[] nodeList;
        private int currentIndex;

        public KeyItr() {
            ArrayList<Node<K, V>> list = new ArrayList<>();
            visit(root, list);

            nodeList = new Object[size];
            list.toArray(nodeList);

            currentIndex = 0;
        }

        public boolean hasNext() {
            return currentIndex < nodeList.length;
        }

        @SuppressWarnings("unchecked")
        public K next() {
            Node<K, V> node = (Node<K, V>) nodeList[currentIndex++];
            return node.getKey();
        }
    }

    public BST_firstImplement() {
        root = null;
    }

    //put key-value pair into BST
    public void put(K key, V value) {
        if (value == null) {
            delete(key);
            return;
        }

        size++;

        if (root == null) {
            root = new Node<>(key, value);
            return;
        }

        Node<K, V> node = root;
        Node<K, V> parent = null;
        while (node != null && !key.equals(node.getKey())) {
            parent = node;
            if (key.compareTo(node.getKey()) < 0) {
                node = node.getLeft();
            } else {
                node = node.getRight();
            }
        }

        if (node == null) {
            if (key.compareTo(parent.getKey()) < 0) {
                parent.setLeft(new Node<>(key, value));
            } else {
                parent.setRight(new Node<>(key, value));
            }
        } else {
            node.setValue(value);
        }
    }

    //value paired with key (null if key is absent)
    public V get(K key) {
        Node<K, V> node = find(key);
        if (node == null) return null;
        return node.getValue();
    }

    //remove key (and its value) from BST
    public void delete(K key) {
        Node<K, V> node = find(key);

        Node<K, V> parent = node.getParent();

        if (parent == null) { // node is root
            root = replacementNode(root);
            if (root != null) {
                root.setParent(null);
            }
        } else { // node != root
            if (key.compareTo(parent.getKey()) < 0) {
                parent.setLeft(replacementNode(node));
            } else {
                parent.setRight(replacementNode(node));
            }
        }

        size--;
    }

    public int size() {
        return size;
    }

    //all keys in the table
    public Iterable<K> iterator() {
        return new Iterable<K>() {
            public Iterator iterator() {
                return new KeyItr();
            }
        };
    }

    private Node<K, V> find(K key) {
        Node<K, V> node = root;

        while (node != null) {
            int cmp = key.compareTo(node.getKey());

            if (cmp < 0) {
                node = node.getLeft();
            } else if (cmp > 0) {
                node = node.getRight();
            } else {
                return node;
            }
        }

        return null;
    }

    private Node<K, V> replacementNode(Node<K, V> node) {
        if (node.getLeft() == null) return node.getRight();
        if (node.getRight() == null) return node.getLeft();
        move(node.getLeft(), node.getRight());
        return node.getRight();
    }

    private void move(Node<K, V> X, Node<K, V> Y) {
        Node<K, V> node = Y;
        while (node.getLeft() != null) node = node.getLeft(); // find the smallest key in Y
        node.setLeft(X);
    }

    private void visit(Node<K, V> node, ArrayList<Node<K, V>> list) {
        if (node == null) return;
        if (node.getLeft() != null) visit(node.getLeft(), list);
        list.add(node);
        if (node.getRight() != null) visit(node.getRight(), list);
    }

    public void print() {
        ArrayList<Node<K, V>> list = new ArrayList<>();
        visit(root, list);
        for (Node<K, V> node : list) {
            System.out.print("<" + node.getKey() + " " + node.getValue() + ">, ");
        }
        System.out.println();
    }
}
