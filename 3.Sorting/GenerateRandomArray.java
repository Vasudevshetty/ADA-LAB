import java.util.Random;

public class GenerateRandomArray {
    public static int[] generateRandomArray(int size, int minVal, int maxVal) {
        Random rand = new Random();
        int array[] = new int[size + 1];

        for (int i = 0; i < size; i++)
            array[i] = minVal + rand.nextInt(maxVal - minVal + 1);

        return array;
    }
}
