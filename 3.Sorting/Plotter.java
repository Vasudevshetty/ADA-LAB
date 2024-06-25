import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

public class Plotter {
    private int[] reverse(int[] array) {
        for (int i = 0, j = array.length - 1; i < j; i++, j--) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        return array;
    }

    public void plot(String sortType) {
        try (FileWriter dataFile = new FileWriter("./data/" + sortType + "_sort.dat")) {
            int minVal = 10;
            int maxVal = 1000;

            dataFile.write("#size best average worst\n");

            boolean divideOrBrute = sortType.equals("merge") || sortType.equals("quick");

            for (int size = divideOrBrute ? 2 : 10; size <= (divideOrBrute ? 1024 : 100); size = divideOrBrute
                    ? size * 2
                    : size + 10) {
                int[] bestArray = GenerateRandomArray.generateRandomArray(size, minVal, maxVal);

                Arrays.sort(bestArray);

                int best = Sorting.sort(bestArray, sortType);
                int average = Sorting.sort(GenerateRandomArray.generateRandomArray(size, minVal, maxVal), sortType);
                int worst = Sorting.sort(reverse(bestArray), sortType);

                dataFile.write(size + " " + best + " " + average + " " + worst + "\n");
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        Plotter plot = new Plotter();
        String sortType = args[0];
        plot.plot(sortType);
    }
}
