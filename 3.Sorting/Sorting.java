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
                    swap(array, j, j + 1);
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

    private static int insertionSort(int[] array) {
        int count = 0;
        for (int i = 1; i < array.length; i++) {
            int min = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > min) {
                array[j + 1] = array[j];
                j--;
                count++;
            }
            array[j + 1] = min;
        }
        return count;
    }

    private static int quickSort(int[] array) {
        return quickSort(array, 0, array.length - 1);
    }

    private static int quickSort(int[] array, int low, int high) {
        int count = 0;
        if (low < high) {
            int[] partitionResult = partition(array, low, high);
            int pi = partitionResult[0];
            count += partitionResult[1];
            count += quickSort(array, low, pi - 1);
            count += quickSort(array, pi + 1, high);
        }
        return count;
    }

    private static int[] partition(int[] array, int low, int high) {
        int pivot = array[high];
        int i = low - 1;
        int count = 0;
        for (int j = low; j < high; j++) {
            count++;
            if (array[j] < pivot) {
                i++;
                swap(array, i, j);
            }
        }
        swap(array, i + 1, high);
        return new int[] { i + 1, count };
    }

    private static int mergeSort(int[] array) {
        return mergeSort(array, 0, array.length - 1);
    }

    private static int mergeSort(int[] array, int left, int right) {
        int count = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;
            count += mergeSort(array, left, mid);
            count += mergeSort(array, mid + 1, right);
            count += merge(array, left, mid, right);
        }
        return count;
    }

    private static int merge(int[] array, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[] L = new int[n1];
        int[] R = new int[n2];

        System.arraycopy(array, left, L, 0, n1);
        System.arraycopy(array, mid + 1, R, 0, n2);

        int i = 0, j = 0, k = left;
        int count = 0;

        while (i < n1 && j < n2) {
            count++;
            if (L[i] <= R[j]) {
                array[k++] = L[i++];
            } else {
                array[k++] = R[j++];
            }
        }

        while (i < n1) {
            array[k++] = L[i++];
        }

        while (j < n2) {
            array[k++] = R[j++];
        }

        return count;
    }

    public static int sort(int[] array, String sortType) {
        if (sortType.equals("bubble"))
            return bubbleSort(array);
        if (sortType.equals("selection"))
            return selectionSort(array);
        if (sortType.equals("insertion"))
            return insertionSort(array);
        if (sortType.equals("merge"))
            return mergeSort(array);
        if (sortType.equals("quick"))
            return quickSort(array);
        return -1;
    }
}
