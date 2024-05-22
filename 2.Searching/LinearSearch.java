import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

class LinearSearchResult {
    public final int index;
    public final int comparisons;

    public LinearSearchResult(int index, int comparisons) {
        this.index = index;
        this.comparisons = comparisons;
    }
}

public class LinearSearch {
    public static LinearSearchResult binarySearch(int[] array, int key) {
        int count = 0;

        for (int i = 0; i < array.length; i++) {
            count++;
            if (array[i] == key)
                return new LinearSearchResult(i, count);
        }

        count++;
        return new LinearSearchResult(-1, count);
    }

    public static void main(String args[]) throws IOException {
        int minVal = 1;
        int maxVal = 100000;

        Files.createDirectories(Paths.get("./2.Searching/data/linearSearch"));

        try (FileWriter dataFile = new FileWriter("./2.Searching/data/linearSearch/linear_search_time.dat")) {
            dataFile.write("#Size Best Average Worst\n");

            for (int size = 100; size <= 1000; size += 100) {
                int[] array = GenearteRandomArray.genearteRandomArray(size, minVal, maxVal);
                Arrays.sort(array);

                LinearSearchResult bestTime = binarySearch(array, array[0]);
                LinearSearchResult averageTime = binarySearch(array, array[array.length / 2]);
                LinearSearchResult worstTime = binarySearch(array, array[array.length - 1]);

                dataFile.write(size + " " + bestTime.comparisons + " " + averageTime.comparisons + " "
                        + worstTime.comparisons + "\n");
            }
        }

    }
}