public class WeightedQuickUnionUF {
    private int[] lab;
    private int[] size;

    public WeightedQuickUnionUF(int numNode) {
        lab = new int[numNode];
        size = new int[numNode];

        for (int i = 0; i < numNode; i++) {
            lab[i] = i;
            size[i] = 1;
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
        return root(nodeA) == root(nodeB);
    }
/*
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input Number Of Node: ");
        int numNode = sc.nextInt();

        //initialize
        WeightedQuickUnionUF QU = new WeightedQuickUnionUF(numNode);

        String stmt = "";
        while (true) {
            System.out.println("Input Query: (type 'end' to exit)");

            stmt = sc.next();

            //check if user want to exit
            if (stmt.equals("exit")) {
                break;
            }

            //get input nodes
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
