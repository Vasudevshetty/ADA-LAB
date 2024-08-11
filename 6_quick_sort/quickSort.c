#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *array, int low, int high)
{
    int pivot = array[low];
    int i = low, j = high + 1;

    do
    {
        do
        {
            count++;
            i++;
        } while (i <= high && array[i] < pivot);
        do
        {
            count++;
            j--;
        } while (j >= low && array[j] > pivot);

        if (i < j)
            swap(&array[i], &array[j]);
    } while (i < j);

    swap(&array[low], &array[j]);
    return j;
}

void quickSort(int *array, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}

void test()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int array[n];
    printf("Enter elements: \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    quickSort(array, 0, n);
    printf("The sorted array is (using quick-sort): \n");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void plotter()
{
    FILE *data = fopen("quickSort_results.dat", "w");
    fprintf(data, "#size best avg worst\n");
    for (int n = 2; n <= 1024; n *= 2)
    {
        int *arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            arr[i] = 4;
        count = 0;
        quickSort(arr, 0, n - 1);
        int bestCase = count;

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count = 0;
        quickSort(arr, 0, n - 1);
        int avgCase = count;

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count = 0;
        quickSort(arr, 0, n - 1);
        int worstCase = count;

        fprintf(data, "%d %d %d %d\n", n, bestCase, avgCase, worstCase);
    }
    fclose(data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <plot|test>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "plot") == 0)
        plotter();

    if (strcmp(argv[1], "test") == 0)
        test();

    return 0;
}
