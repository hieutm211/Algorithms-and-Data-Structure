import java.util.Scanner;

public class UF {
    private int[] lab;
    private int[] size;

    public UF(int numNode) {
        lab = new int[numNode];
        size = new int[numNode];

        for (int i = 0; i < numNode; i++) {
            lab[i] = i;
            size[i] = 1;
        }
    }

    private void validate(int node) {
        int n = lab.length;
        if (node < 0 || n <= node) {
            throw new IllegalArgumentException("index " + node + " is not in [0..n-1]");
        }
    }

    private int root(int node) {
        validate(node);

        int p = node;
        while (lab[p] != p) {
            p = lab[p];
        }
        lab[node] = p;
        return lab[node];
    }

    public void union(int nodeA, int nodeB) {
        validate(nodeA);
        validate(nodeB);

        int rootA = root(nodeA);
        int rootB = root(nodeB);
        if (rootA != rootB) {
            //make sure that size[rootA] >= size[rootB]
            if (size[rootA] < size[rootB]) {
                int temp = rootA;
                rootA = rootB;
                rootB = temp;
            }

            //connect rootB to rootA
            lab[rootB] = rootA;
            size[rootA] += size[rootB];
        }
    }

    public boolean connected(int nodeA, int nodeB) {
        validate(nodeA);
        validate(nodeB);

        return root(nodeA) == root(nodeB);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input Number Of Node: ");
        int numNode = sc.nextInt();

        //initialize
        UF uf = new UF(numNode);

        String stmt = "";
        while (true) {
            System.out.println("Input Query: (type 'end' to exit)");

            stmt = sc.next();

            //check if user want to exit
            if (stmt.equals("exit")) {
                break;
            }

            //get input nodes
            int firstNode = sc.nextInt() - 1;
            int secondNode = sc.nextInt() - 1;

            switch (stmt.charAt(0)) {
                case 'u':
                    //perform an "union" query
                    uf.union(firstNode, secondNode);
                    break;
                case 'c':
                    //perform a "connected" query
                    boolean answer = uf.connected(firstNode, secondNode);
                    System.out.println(answer);
                    break;
            }
        }

        sc.close();
    }
}
