import java.util.Random;

public class GenearteRandomArray {
    public static int[] genearteRandomArray(int size, int minVal, int maxVal) {
        int array[] = new int[size + 1];
        Random rand = new Random();
        for (int i = 0; i < size; i++)
            array[i] = minVal + rand.nextInt(maxVal - minVal + 1);
        return array;
    }
}
