import java.io.FileWriter;
import java.io.IOException;

public class StringMatchingBenchmark {
    private int stringMatching(String text, String pattern) {
        int count = 0;
        for (int i = 0; i <= text.length() - pattern.length(); i++) {
            int j = 0;
            while (j < pattern.length()) {
                count++;
                if (pattern.charAt(j) != text.charAt(i + j)) {
                    j++;
                    break;
                }
            }
        }
        return count;
    }

    public void plot() {
        try (FileWriter file = new FileWriter("./string_data.dat")) {
            StringBuilder text = new StringBuilder();
            for (int i = 0; i < 1000; i++)
                text.append('a');

            file.write("#size best average worst\n");
            int length = 10;
            while (length <= 1000) {
                StringBuilder pattern = new StringBuilder();
                for (int i = 0; i < length; i++) {
                    pattern.append('a');
                }
                int worst = stringMatching(text.toString(), pattern.toString());
                pattern.setCharAt(length - 1, 'b'); // Calculate worst case first

                int average = stringMatching(text.toString(), pattern.toString()); // Then average case
                pattern.setCharAt(length - 1, 'a'); // Reset pattern for best case calculation

                int best = stringMatching(text.toString(), pattern.toString());

                file.write(length + " " + best + " " + average + " " + worst + "\n");

                length += length < 100 ? 10 : 100;
            }
        } catch (IOException e) {
            System.out.println("An error occurred while writing to files.");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        StringMatchingBenchmark string = new StringMatchingBenchmark();
        string.plot();
    }
}
