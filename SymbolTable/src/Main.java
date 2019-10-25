import java.util.Iterator;
import java.util.Scanner;

public class Main {

    private static final Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        OrderedST<String, Integer> ST = new OrderedST<>();

        for (String query = sc.next(); !query.equals("stop"); query = sc.next()) {
            switch (query) {
                case "put":
                    String key = sc.next();
                    String value = sc.next();
                    if (value.equals("null")) ST.put(key, null);
                    else ST.put(key, Integer.parseInt(value));
                    break;
                case "get":
                    System.out.println(ST.get(sc.next()));
                    break;
                case "delete":
                    ST.delete(sc.next());
                    break;
                case "contains":
                    System.out.println(ST.contains(sc.next()));
                    break;
                case "isEmpty":
                    System.out.println(ST.isEmpty());
                    break;
                case "size":
                    System.out.println(ST.size());
                    break;
                case "min":
                    System.out.println(ST.min());
                    break;
                case "max":
                    System.out.println(ST.max());
                    break;
                case "floor":
                    System.out.println(ST.floor(sc.next()));
                    break;
                case "ceiling":
                    System.out.println(ST.ceiling(sc.next()));
                    break;
                case "rank":
                    System.out.println(ST.rank(sc.next()));
                    break;
                case "select":
                    System.out.println(ST.select(sc.nextInt()));
                    break;
                case "deleteMin":
                    ST.deleteMin();
                    break;
                case "deleteMax":
                    ST.deleteMax();
                    break;
                case "sizek":
                    System.out.println(ST.size(sc.next(), sc.next()));
                    break;

                case "listKey":
                    Iterator<String> it = ST.keys().iterator();
                    while (it.hasNext()) {
                        System.out.print(it.next() + " ");
                    }
                    System.out.println();
                    break;

                case "listKeyRange":
                    it = ST.keys(sc.next(), sc.next()).iterator();
                    while (it.hasNext()) {
                        System.out.print(it.next() + " ");
                    }
                    System.out.println();
                    break;

                default:
                    System.out.println("unknown query");
            }
            ST.print();
        }
    }
}
