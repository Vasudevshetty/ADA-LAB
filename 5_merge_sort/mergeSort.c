#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

void merge(int array[], int low, int mid, int high)
{
    int n1 = (mid - low) + 1;
    int n2 = high - mid;
    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = array[low + i];
    for (int i = 0; i < n2; i++)
        right[i] = array[mid + i + 1];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        count++;
        if (left[i] <= right[j])
            array[k++] = left[i++];
        else
            array[k++] = right[j++];
    }

    while (i < n1)
        array[k++] = left[i++];
    while (j < n2)
        array[k++] = right[j++];
}

void mergeSort(int array[], int low, int high)
{
    if (low < high)
    {
        int mid = (high + low) / 2;
        mergeSort(array, low, mid);
        mergeSort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

void worst(int *arr, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int a[n1], b[n2];

        for (int i = 0; i < n1; i++)
            a[i] = arr[2 * i];
        for (int i = 0; i < n2; i++)
            b[i] = arr[2 * i + 1];

        worst(a, 0, n1 - 1);
        worst(b, 0, n2 - 1);

        for (int i = 0; i < n1; i++)
            arr[i] = a[i];

        for (int i = 0; i < n2; i++)
            arr[n1 + i] = b[i];
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
    mergeSort(array, 0, n);
    printf("The sorted array is (using mergesort): \n");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void plotter()
{
    srand(time(NULL));
    FILE *data = fopen("./merge_results.dat", "w");

    fprintf(data, "#Size Best Average Worst\n");

    for (int n = 2; n <= 1024; n *= 2)
    {
        int *arr = (int *)malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count = 0;
        mergeSort(arr, 0, n - 1);
        int bestCase = count;

        count = 0;
        worst(arr, 0, n - 1);
        mergeSort(arr, 0, n - 1);
        int worstCase = count;

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count = 0;
        mergeSort(arr, 0, n - 1);
        int avgCase = count;

        fprintf(data, "%d %d %d %d\n", n, bestCase, avgCase, worstCase);
    }
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
    else if (strcmp(argv[1], "test") == 0)
        test();
    else
        printf("Invalid option. Use 'plot' or 'test'.\n");

    return 0;
}