import java.util.Comparator;
import java.util.PriorityQueue;

public class Main {

    public static void main(String[] args) {
        java.util.Scanner sc = new java.util.Scanner(System.in);

        int n = sc.nextInt();
        Heap<Double> heap = new Heap<>();

        while (n-- > 0) {
            heap.add(sc.nextDouble());
            System.out.println("current peek: " + heap.peek());
        }

        sc.close();

        while (!heap.isEmpty()) {
            System.out.print(heap.poll() + " ");
        }
    }
}
