public class StringMatchingBenchmark {
    private int stringMathching(String text, String pattern) {
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
            if (j == text.length())
                return count;
        }
        return count;
    }
}
