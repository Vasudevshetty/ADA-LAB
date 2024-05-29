public class Sorting {
    private static void swap(int array[], int x, int y) {
        int temp = array[x];
        array[x] = array[y];
        array[y] = temp;
    }

    private static int bubbleSort(int[] array) {
        int count = 0;

        for (int i = 0; i < array.length; i++) {
            boolean flag = false;
            for (int j = 0; j < array.length - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    flag = true;
                    swap(array, i, j);
                }
                count++;
            }
            if (!flag)
                break;
        }

        return count;
    }

    private static int selectionSort(int[] array) {
        int count = 0;

        for (int i = 0; i < array.length - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < array.length; j++) {
                if (array[i] < array[min_idx])
                    min_idx = j;
                count++;
            }
            if (min_idx != i)
                swap(array, i, min_idx);
        }
        return count;
    }

    public static int sort(int[] array, String sortType) {
        if (sortType.equals("bubble"))
            return bubbleSort(array);
        if (sortType.equals("selection"))
            return selectionSort(array);

        return -1;
    }
}
