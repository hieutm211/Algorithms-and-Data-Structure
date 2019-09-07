
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SortOddNumbers {
    public static boolean isOdd(Integer x) {
        return x % 2 != 0;
    }

    public static void sort(Integer[] arr, List<Integer> positionList, int lo, int hi) {
        if (lo >= hi) return;

        int i = lo, j = hi;
        Integer mid = arr[positionList.get(lo + (hi-lo)/2)];

        while (i <= j) {
            while (arr[positionList.get(i)].compareTo(mid) < 0) i++;
            while (arr[positionList.get(j)].compareTo(mid) > 0) j--;
            if (i <= j) {
                if (i < j) {
                    Integer temp = arr[positionList.get(i)];
                    arr[positionList.get(i)] = arr[positionList.get(j)];
                    arr[positionList.get(j)] = temp;
                }
                i++; j--;
            }
        }
        sort(arr, positionList, lo, j);
        sort(arr, positionList, i, hi);
    }

    public static void sortOdd(Integer[] arr, int begin, int end) {
        List<Integer> oddList = new ArrayList<Integer>();
        for (int i = begin; i < end; i++) {
            if (isOdd(arr[i])) {
                oddList.add(i);
            }
        }
        if (oddList.size() <= 1) return;
        sort(arr, oddList, 0, oddList.size()-1);
    }

    public static void main(String[] args) {
        //Read data
        Scanner sc = new Scanner(System.in);

        int arrlen = sc.nextInt();
        Integer[] arr = new Integer[arrlen];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = sc.nextInt();
        }

        sc.close();

        //Sort
        sortOdd(arr, 0, arr.length);

        //Print the result
        for (int e : arr) {
            System.out.print(e + " ");
        }
    }
}