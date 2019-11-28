import java.util.List;
import java.util.ArrayList;

public class BST<K extends Comparable<K>, V> {

    private Node root;

    private class Node {
        private K key;
        private V value;
        Node left, right;
        int size;

        public Node(K key, V value) {
            this(key, value, null, null, 1);
        }

        public Node(K key, V value, Node left, Node right, int size) {
            this.key = key;
            this.value = value;
            this.left = left;
            this.right = right;
            this.size = size;
        }
    }

    //create a Binary search tree
    public BST() {
        root = null;
    }

    //put key-value pair in to BST
    public void put(K key, V value) {
        root = put(root, key, value);
    }

    //value paired with key (null if key is absent).
    public V get(K key) {
        Node x = root;
        while (x != null) {
            int cmp = key.compareTo(x.key);
            if (cmp < 0) {
                x = x.left;
            } else if (cmp > 0) {
                x = x.right;
            } else {
                return x.value;
            }
        }
        return null;
    }

    //remove key (and its value) from BST
    public void delete(K key) {}

    public boolean contains(K key) {
        return get(key) != null;
    }

    //is BST empty?
    public boolean isEmpty() {
        return root == null;
    }

    //number of key-value pairs.
    public int size() {
        return size(root);
    }

    //smallest key
    public K min() {
        Node node = min(root);
        if (node == null) return null;
        return node.key;
    }

    //largest key
    public K max() {
        Node node = max(root);
        if (node == null) return null;
        return node.key;
    }

    //largest key less than or equal to key
    public K floor(K key) {
        Node node = floor(root, key);
        if (node == null) return null;
        return node.key;
    }

    //smallest key greater than or equal to key
    public K ceiling(K key) {
        Node node = ceiling(root, key);
        if (node == null) return null;
        return node.key;
    }

    //number of keys less than key
    public int rank(K key) {
        return rank(root, key);
    }

    //key of rank k
    public K select(int k) {
        Node node = select(root, k);
        if (node == null) return null;
        return node.key;
    }

    //delete smallest key
    public void deleteMin() {}

    //delete largest key
    public void deleteMax() {}

    //number of keys in [lo..hi]
    public int size(K lo, K hi) {
        if (isEmpty()) return 0;
        if (hi.compareTo(lo) < 0) return 0;
        K keyMin = min();
        K keyMax = max();
        if (hi.compareTo(keyMin) < 0 || keyMax.compareTo(lo) < 0) return 0;
        if (keyMax.compareTo(hi) < 0) return rank(hi) - rank(lo);
        return rank(hi) - rank(lo) + 1;
    }

    //keys in [lo..hi], in sorted order
    public Iterable<K> keys(K lo, K hi) {
        return null;
    }

    //all keys in the BST, in sorted order.
    public Iterable<K> keys() {
        return null;
    }

    public void printPairs() {
        List<Node> list = new ArrayList<>();
        visit(root, list);

        System.out.print("BST: ");
        for (Node node: list) {
            System.out.print("<" + node.key + ", " + node.value + ">, ");
        }
        System.out.println();
    }

    private void visit(Node node, List<Node> list) {
        if (node == null) return;
        visit(node.left, list);
        list.add(node);
        visit(node.right, list);
    }

    private int size(Node node) {
        if (node == null) return 0;
        return node.size;
    }

    //put newNode into tree x
    private Node put(Node x, K key, V value) {
        if (x == null) return new Node(key, value);
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = put(x.left, key, value);
        } else if (cmp > 0) {
            x.right = put(x.right, key, value);
        } else {
            x.value = value;
        }

        x.size = size(x.left) + size(x.right) + 1;

        return x;
    }

    private Node min(Node x) {
        if (x == null) return null;
        while (x.left != null) {
            x = x.left;
        }
        return x;
    }

    private Node max(Node x) {
        if (x == null) return null;
        while (x.right != null) {
            x = x.right;
        }
        return x;
    }

    private Node floor(Node x, K key) {
        if (x == null) return null;
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return floor(x.left, key);
        } else if (cmp > 0) {
            Node temp = floor(x.right, key);
            if (temp == null) return x;
            return temp;
        }
        return x;
    }

    private Node ceiling(Node x, K key) {
        if (x == null) return null;
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            Node temp = ceiling(x.left, key);
            if (temp == null) return x;
            return temp;
        } else if (cmp > 0) {
            return ceiling(x.right, key);
        }
        return x;
    }

    private Node select(Node x, int k) {
        if (x == null) return null;

        if (size(x.left) < k) {
            return select(x.right, k - size(x.left) - 1);
        } else if (size(x.left) > k) {
            return select(x.left, k);
        }
        return x;
    }

    private int rank(Node x, K key) {
        if (x == null) return 0;
        int cmp = key.compareTo(x.key);
        if (cmp < 0) return rank(x.left, key);
        else if (cmp > 0) return 1 + size(x.left) + rank(x.right, key);
        return size(x.left);
    }
}
