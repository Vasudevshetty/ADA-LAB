class SearchResult {
    final public int index;
    final public int comparisons;

    public SearchResult(int index, int comparisons) {
        this.index = index;
        this.comparisons = comparisons;
    }
}

public class Searching {
    private static SearchResult binarySearch(int[] array, int key) {
        return binarySearchR(array, key, 0, array.length - 1, 0);
    }

    private static SearchResult binarySearchR(int[] array, int key, int low, int high, int comparisons) {
        if (low <= high) {
            int mid = low + (high - low) / 2;
            comparisons++;
            if (array[mid] == key)
                return new SearchResult(mid, comparisons);
            else if (array[mid] < key)
                return binarySearchR(array, key, mid + 1, high, comparisons);
            else
                return binarySearchR(array, key, low, mid - 1, comparisons);
        }
        return new SearchResult(-1, comparisons);
    }

    private static SearchResult linearSearch(int[] array, int key) {
        int comparsions = 0;
        for (int i = 0; i < array.length; i++) {
            comparsions++;
            if (array[i] == key)
                return new SearchResult(i, comparsions);
        }
        return new SearchResult(-1, comparsions);
    }

    public static SearchResult search(int[] array, int key, String searchType) {
        if (searchType.equals("linear"))
            return linearSearch(array, key);
        if (searchType.equals("binary"))
            return binarySearch(array, key);

        return null;
    }
}
