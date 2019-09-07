import java.util.Scanner;

public class FindMedian {
    public static void quickSort(int[] arr, int lo, int hi) {
        if (lo >= hi) return;
        
        int i = lo, j = hi;
        int mid = arr[lo + ((int) (Math.random() * (hi - lo)))];

        while (i <= j) {
            while (arr[i] < mid) i++;
            while (arr[j] > mid) j--;
            if (i <= j) {
                if (i < j) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
                i++; j--;
            }
        }
        quickSort(arr, lo, j);
        quickSort(arr, i, hi);
    }

    public static void sort(int[] arr) {
        quickSort(arr, 0, arr.length-1);
    }

    public static double medianOf(int[] arr) {
        int[] temp = arr.clone();
        sort(temp);

        int idxMid = (temp.length) / 2;
        if (temp.length%2 == 0) {
            return (double) (arr[idxMid] + arr[idxMid+1])/2;
        } else {
            return arr[idxMid];
        }
    }
    public static void main(String[] args) {
        //read data
        Scanner sc = new Scanner(System.in);

        int arrLen = sc.nextInt();
        int[] arr = new int[arrLen];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = sc.nextInt();
        }

        sc.close();

        //find median
        double median = medianOf(arr);

        //print result
        if (arr.length%2 == 0)  System.out.println(median);
        else                    System.out.println((int)(median));
    }
}
