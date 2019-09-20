import java.util.Scanner;

public class QuickFindUF {
    private int[] lab;
    private int numComponent;

    public QuickFindUF(int numNode) {
        lab = new int[numNode];
        for (int i = 0; i < numNode; i++) {
            lab[i] = i;
        }

        numComponent = numNode;
    }

    public int countComponent() {
        return numComponent;
    }

    public void union(int nodeA, int nodeB) {
        int rootA = lab[nodeA];
        int rootB = lab[nodeB];
        for (int i = 0; i < lab.length; i++) {
            if (lab[i] == rootB) {
                lab[i] = rootA;
            }
        }

        numComponent--;
    }

    public boolean connected(int nodeA, int nodeB) {
        return lab[nodeA] == lab[nodeB];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input Number Of Node: ");
        int numNode = sc.nextInt();

        //initialize
        QuickFindUF uf = new QuickFindUF(numNode);

        String stmt = "";
        while (!stmt.equals("end")) {
            System.out.println(uf.countComponent() + " - Input Query: (type 'end' to exit)");

            stmt = sc.next();
            int firstNode = sc.nextInt() - 1;
            int secondNode = sc.nextInt() - 1;

            if (stmt.equals("union")) {
                //perform an "union" query
                uf.union(firstNode, secondNode);
            } else {
                //perform a "connected" query
                boolean answer = uf.connected(firstNode, secondNode);
                System.out.println(answer);
            }
        }

        sc.close();
    }
}