public class QuickUnionUF {
    private int[] lab;

    public QuickUnionUF(int numNode) {
        lab = new int[numNode];
        for (int i = 0; i < numNode; i++) {
            lab[i] = i;
        }
    }

    private int root(int node) {
        while (lab[node] != node) {
            node = lab[node];
        }
        return node;
    }

    public void union(int nodeA, int nodeB) {
        int rootA = root(nodeA);
        int rootB = root(nodeB);
        if (rootA != rootB) {
            lab[rootB] = rootA;
        }
    }

    public boolean connected(int nodeA, int nodeB) {
        return root(nodeA) == root(nodeB);
    }

/*
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input Number Of Node: ");
        int numNode = sc.nextInt();

        //initialize
        QuickUnionUF QU = new QuickUnionUF(numNode);

        String stmt = "";
        while (!stmt.equals("end")) {
            System.out.println("Input Query: (type 'end' to exit)");

            stmt = sc.next();
            int firstNode = sc.nextInt()-1;
            int secondNode = sc.nextInt()-1;

            if (stmt.equals("union")) {
                //perform an "union" query
                QU.union(firstNode, secondNode);
            } else {
                //perform a "connected" query
                boolean answer = QU.connected(firstNode, secondNode);
                System.out.println(answer);
            }
        }

        sc.close();
    }
*/
}
