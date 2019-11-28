package SubstringSearch;

import java.util.ArrayList;
import java.util.List;

public class KMP_NFA {
    private int[] nfa;
    private String pattern;
    private int M;

    public void setPattern(String pattern) {
        this.pattern = pattern;
        this.M = pattern.length();
        initiate();
    }

    public List<Integer> search(String text) {
        ArrayList<Integer> list = new ArrayList<>();
        int k = 0;
        for (int i = 0; i < text.length(); i++) {
            while (k > 0 && pattern.charAt(k) != text.charAt(i)) k = nfa[k];
            if (pattern.charAt(k) == text.charAt(i)) k++;
            if (k == M) {
                list.add(i-M+1);
                k = nfa[k];
            }
        }
        return list;
    }

    public int find(String text) {
        int k = 0;
        for (int i = 0; i < text.length(); i++) {
            while (k > 0 && pattern.charAt(k) != text.charAt(i)) {
                k = nfa[k];
            }
            if (pattern.charAt(k) == text.charAt(i)) {
                k++;
            }
            if (k == M) return i-M+1;
        }
        return -1;
    }

    private void initiate() {
        nfa = new int[M+1];

        nfa[0] = 0;

        int k = 0;

        for (int i = 1; i < M; i++) {
            nfa[i] = k;
            while (k > 0 && pattern.charAt(k) != pattern.charAt(i)) {
                k = nfa[k];
            }
            if (pattern.charAt(k) == pattern.charAt(i)) {
                k++;
            }
        }

        nfa[M] = k;
    }
}
