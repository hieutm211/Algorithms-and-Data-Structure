package SubstringSearch;

import java.util.List;
import java.util.Scanner;

public class Main {

    private static final Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        String text = sc.nextLine();
        String pattern = sc.nextLine();

        KMP_DFA kmp = new KMP_DFA(new char[]{'A', 'B', 'C'});
        kmp.setPattern(pattern);

        List<Integer> results = kmp.search(text);
        System.out.println(results.toString());

        System.out.println(kmp.find(text));
    }
}
