package SubstringSearch;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class KMP_DFA {
    private int R;
    private int M;
    private int[][] dfa;
    private HashMap<Character, Integer> map = new HashMap<>();

    public KMP_DFA(char[] charList) {
        R = charList.length;
        for (int i = 0; i < charList.length; i++) {
            map.put(charList[i], i);
        }
    }

    public void setPattern(String pattern) {
        if (pattern.isEmpty()) {
            return;
        }

        M = pattern.length();

        dfa = new int[R][M+1];

        int c = map.get(pattern.charAt(0));
        dfa[c][0] = 1;

        int X = 0;
        for (int k = 1; k < M; k++) {
            c = map.get(pattern.charAt(k));

            //copy from state X
            //calculate mismatch transition
            for (int i = 0; i < R; i++) {
                dfa[i][k] = dfa[i][X];
            }

            //calculate match transition
            dfa[c][k] = k+1;

            //maintain state X for pat[1..k-1]

            X = dfa[c][X];
        }

        for (int i = 0; i < R; i++) {
            dfa[i][M] = dfa[i][X];
        }
    }

    public List<Integer> search(String text) {
        ArrayList<Integer> list = new ArrayList<>();

        int state = 0;
        for (int i = 0; i < text.length(); i++) {
            int c = map.get(text.charAt(i));;
            state = dfa[c][state];
            if (state == M) {
                list.add(i-M+1);
            }
        }
        return list;
    }

    public boolean find(String text) {
        int state = 0;
        for (int i = 0; i < text.length(); i++) {
            int c = map.get(text.charAt(i));
            state = dfa[c][state];
            if (state == M) {
                return true;
            }
        }
        return false;
    }
}
