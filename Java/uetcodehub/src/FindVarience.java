import java.util.Scanner;
import java.util.Arrays;

public class FindVarience {
    public static double averageOf(double[] arr) {
        double average = 0;
        for (double e : arr) {
            average += e;
        }
        average /= arr.length;
        return average;
    }

    public static double varienceOf(double[] arr) {
        double varience = 0;
        double average = averageOf(arr);
        for (double e : arr) {
            varience += (e-average) * (e-average);
        }
        varience /= arr.length;
        return varience;
    }
    public static void main(String[] args) {
        //read data
        Scanner sc = new Scanner(System.in);

        int arrLen = sc.nextInt();
        double[] arr = new double[arrLen];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = sc.nextDouble();
        }

        sc.close();

        //find average
        double average = averageOf(arr);

        //calculate varience
        double varience = varienceOf(arr);

        //print result
        System.out.println(((int) average) + " " + ((int) varience));
    }
}