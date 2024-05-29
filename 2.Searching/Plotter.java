import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Plotter {
    private void plot(String search) {
        int minVal = 1;
        int maxVal = 1000;
        Random rand = new Random();

        try (FileWriter dataFile = new FileWriter("./data/" + search + "_search.dat")) {

            dataFile.write("#size best average worst\n");
            boolean searchIsLinear = search.equals("linear");
            int size = search.equals("linear") ? 100 : 2;
            while (size <= 10000) {
                int[] array = GenearteRandomArray.genearteRandomArray(size, minVal, maxVal);

                SearchResult best = Searching.search(array, array[searchIsLinear ? 0 : array.length / 2], search);
                SearchResult average = Searching.search(array,
                        array[searchIsLinear ? rand.nextInt(size) : array.length / 4], search);
                SearchResult worst = Searching.search(array, searchIsLinear ? array[array.length - 1] : -1, search);

                dataFile.write(size + " " + best.comparisons + " " + average.comparisons + " " + worst.comparisons + "\n");

                size = searchIsLinear ? size + 100 : size * 2;
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        Plotter plot = new Plotter();
        String search = args[0];
        plot.plot(search);
    }
}
