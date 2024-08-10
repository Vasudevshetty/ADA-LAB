import java.io.FileWriter;
import java.io.IOException;

public class StringMatchingBenchmark {

    // String matching method
    private int stringMatching(String text, String pattern) {
        int count = 0;
        for (int i = 0; i <= text.length() - pattern.length(); i++) {
            int j = 0;
            while (j < pattern.length()) {
                count++;
                if (pattern.charAt(j) != text.charAt(i + j))
                    break;

                j++;
            }
            if (j == pattern.length())
                return count;
        }
        return count;
    }

    // Method to plot the benchmark data
    public void plot() {
        try (FileWriter file = new FileWriter("./string_data.dat")) {
            StringBuilder text = new StringBuilder();
            for (int i = 0; i < 1000; i++) {
                text.append('a');
            }

            file.write("#size best average worst\n");
            int length = 10;
            while (length <= 1000) {
                StringBuilder pattern = new StringBuilder();
                for (int i = 0; i < length; i++) {
                    pattern.append('a');
                }

                int best = stringMatching(text.toString(), pattern.toString());

                pattern.setCharAt(length - 1, 'b'); // Reset pattern for worst case calculation
                int worst = stringMatching(text.toString(), pattern.toString());

                for (int i = 0; i < length; i++) {
                    char[] chars = { 'a', 'b', 'c' };
                    pattern.setCharAt(i, chars[(int) (Math.random() * chars.length)]);

                }

                int average = stringMatching(text.toString(), pattern.toString());
                file.write(length + " " + best + " " + average + " " + worst + "\n");

                length += length < 100 ? 10 : 100;
            }
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }

    // Test case to verify the stringMatching method
    public void testStringMatching() {
        String text = "abcabcabc";
        String pattern = "abc";
        int comparisons = stringMatching(text, pattern);
        System.out.println("Text: " + text);
        System.out.println("Pattern: " + pattern);
        System.out.println("Comparisons: " + comparisons);
    }

    // Main method
    public static void main(String[] args) {
        StringMatchingBenchmark benchmark = new StringMatchingBenchmark();
        benchmark.plot();
        benchmark.testStringMatching(); // Add a test case to the main method
    }
}
