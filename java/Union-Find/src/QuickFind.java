import java.util.Scanner;

public class QuickFind {
    private static int numNode;
    private static int[] id;

    private static int getNumNode() {
        return numNode;
    }

    private static int[] getId() {
        return id;
    }

    private static void updateNumNode(int _numNode) {
        numNode = _numNode;
    }
    private static void updateId(int[] _id) {
        id = _id;
    }
    private static void updateId(int idx, int value) {
        id[idx] = value;
    }

    private static int getId(int idx) {
        return id[idx];
    }

    private static boolean isNode(int nodeId) {
        return 0 <= nodeId && nodeId < getNumNode();

    }

    public static void init(int _numNode) {
        updateNumNode(_numNode);
        updateId(new int[_numNode]);
        for (int i = 0; i < getNumNode(); i++) {
            updateId(i, i);
        }
    }

    public static boolean union(int node1, int node2) {
        if (!isNode(node1) || !isNode(node2)) return false;

        int temp = getId(node2);
        for (int i = 0; i < getNumNode(); i++) {
            if (getId(i) == temp) {
                updateId(i, id[node1]);
            }
        }
        return true;
    }

    public static boolean connected(int node1, int node2) {
        if (!isNode(node1) || !isNode(node2)) return false;

        return getId(node1) == getId(node2);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input Number Of Node: ");
        int numNode = sc.nextInt();
        init(numNode);

        String stmt = "";
        while (!stmt.equals("end")) {
            System.out.println("Input Query: (type 'end' to exit)");

            stmt = sc.next();
            int firstNode = sc.nextInt()-1;
            int secondNode = sc.nextInt()-1;
            if (!isNode(firstNode) || !isNode(secondNode)) {
                System.out.println("number is not valid");
                continue;
            }

            if (stmt.equals("union")) {
                union(firstNode, secondNode);
            } else { //stmt is "query"
                System.out.println(connected(firstNode, secondNode));
            }
        }

        sc.close();
    }
}
