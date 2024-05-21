import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

class BinarySearchResult {
    public final int index;
    public final int comparisons;

    public BinarySearchResult(int index, int comparisons) {
        this.index = index;
        this.comparisons = comparisons;
    }
}

public class BinarySearch {
    public static BinarySearchResult binarySearch(int[] array, int key) {
        int count = 0;
        int low = 0, high = array.length - 1;

        while (low <= high) {
            count++;
            int mid = low + (high - low) / 2;
            if (array[mid] == key)
                return new BinarySearchResult(mid, count);
            else if (array[mid] < key)
                low = mid + 1;
            else
                high = mid - 1;
        }

        count++;
        return new BinarySearchResult(-1, count);
    }

    public static void main(String args[]) throws IOException {
        int minVal = 1;
        int maxVal = 100000;

        Files.createDirectories(Paths.get("./2.Searching/data/binarySearch"));

        try (FileWriter dataFile = new FileWriter("./2.Searching/data/binarySearch/binary_search_time.dat")) {
            dataFile.write("#Size Best Average Worst\n");

            for (int size = 100; size <= 1000; size += 100) {
                int[] array = GenearteRandomArray.genearteRandomArray(size, minVal, maxVal);
                Arrays.sort(array);

                BinarySearchResult bestTime = binarySearch(array, array[size / 2]);
                BinarySearchResult averageTime = binarySearch(array, array[array.length / 5]);
                BinarySearchResult worstTime = binarySearch(array, maxVal - 1);

                dataFile.write(size + " " + bestTime.comparisons + " " + averageTime.comparisons + " "
                        + worstTime.comparisons + "\n");
            }
        }

    }
}
