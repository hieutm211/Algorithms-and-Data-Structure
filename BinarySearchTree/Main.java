import java.util.Scanner;

public class Main {

    private static final Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {

        BST<String, Integer> bst = new BST<>();
        for (String[] query = sc.nextLine().split(" "); !query[0].equals("exit"); query = sc.nextLine().split(" ")) {
            switch (query[0]) {
                case "put":
                    String inputKey = query[1];
                    String inputValue = query[2];
                    if (inputValue.equals("null")) bst.put(inputKey, null);
                    else bst.put(inputKey, Integer.parseInt(inputValue));
                    break;

                case "get":
                    System.out.println(bst.get(query[1]));
                    break;

                case "delete":
                    bst.delete(query[1]);
                    break;

                case "contains":
                    System.out.println(bst.contains(query[1]));
                    break;

                case "isEmpty":
                    System.out.println(bst.isEmpty());
                    break;

                case "size":
                    System.out.println(bst.size());
                    break;

                case "min":
                    System.out.println(bst.min());
                    break;

                case "max":
                    System.out.println(bst.max());
                    break;

                case "floor":
                    System.out.println(bst.floor(query[1]));
                    break;

                case "ceiling":
                    System.out.println(bst.ceiling(query[1]));
                    break;

                case "rank":
                    System.out.println(bst.rank(query[1]));
                    break;

                case "select":
                    System.out.println(bst.select(Integer.parseInt(query[1])));
                    break;

                case "deleteMin":
                    bst.deleteMin();
                    break;

                case "deleteMax":
                    bst.deleteMax();
                    break;

                case "sizeLH":
                    System.out.println(bst.size(query[1], query[2]));
                    break;

                case "printLH":
                    System.out.print("BST: ");
                    for (String key: bst.keys(query[1], query[2])) {
                        System.out.print(key + " ");
                    }
                    System.out.println();
                    break;

                case "print":
                    System.out.print("BST: ");
                    for (String key: bst.keys()) {
                        System.out.print(key + " ");
                    }
                    System.out.println();
                    break;

                default:
                    System.out.println("unknown query");
            }

            bst.printPairs();
        }
    }
}
