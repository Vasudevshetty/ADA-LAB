import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

public class BinarySearchV1 {
    public static int binarySearch(int[] array, int key) {
        int low = 0, high = array.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (array[mid] == key)
                return mid;
            else if (array[mid] < key)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return -1;
    }

    public static double measureBinarySearchTime(int[] array, int key) {
        long start = System.nanoTime();
        binarySearch(array, key);
        long end = System.nanoTime();
        return (end - start) / 1e6;
    }

    public static void main(String args[]) throws IOException {
        int minVal = 1;
        int maxVal = 100000;

        Files.createDirectories(Paths.get("./2.Searching/data/binarySearch"));

        try (FileWriter dataFile = new FileWriter("./2.Searching/data/binarySearch/binary_search_system_time.dat")) {
            dataFile.write("#Size Best Average Worst\n");

            for (int size = 1; size <= 10000; size += 100) {
                int[] array = GenearteRandomArray.genearteRandomArray(size, minVal, maxVal);
                Arrays.sort(array);

                double bestTime = measureBinarySearchTime(array, array[size / 2]);
                double worstTime = measureBinarySearchTime(array, array[size / 4]);
                double averageTime = measureBinarySearchTime(array, maxVal);

                dataFile.write(size + "  " + bestTime + " " + averageTime + " " + worstTime + "\n");
            }
        }

    }
}
