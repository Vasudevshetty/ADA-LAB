#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include <string.h>

void plotter(char *sortType)
{
    char filename[250];
    sprintf(filename, "data/%s_results.dat", sortType);

    FILE *data = fopen(filename, "w");
    fprintf(data, "#size best avg worst\n");
    srand(time(NULL));

    // for (int n = 10; n <= 30000; n < 10000 ? (n = n * 10) : (n = n + 10000))
    for (int n = 10; n <= 100; n += 10)
    {
        int *arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        int bestCase = (sortType[0] == 'b') ? bubbleSort(arr, n) : (sortType[0] == 's') ? selectionSort(arr, n)
                                                                                        : insertionSort(arr, n);

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        int avgCase = (sortType[0] == 'b') ? bubbleSort(arr, n) : (sortType[0] == 's') ? selectionSort(arr, n)
                                                                                       : insertionSort(arr, n);

        for (int i = 0; i < n; i++)
            arr[i] = n - i;
        int worstCase = (sortType[0] == 'b') ? bubbleSort(arr, n) : (sortType[0] == 's') ? selectionSort(arr, n)
                                                                                         : insertionSort(arr, n);

        fprintf(data, "%d %d %d %d\n", n, bestCase, avgCase, worstCase);
        free(arr);
    }

    fclose(data);
}
void test(char *sortType)
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements: \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    if (strcmp(sortType, "bubble") == 0)
        bubbleSort(arr, n);
    if (strcmp(sortType, "selection") == 0)
        selectionSort(arr, n);
    if (strcmp(sortType, "insertion") == 0)
        insertionSort(arr, n);

    printf("The sorted elements are (%s)\n", sortType);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <plot|test> <bubble|insertion|selection>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "plot") == 0)
        plotter(argv[2]);
    if (strcmp(argv[1], "test") == 0)
        test(argv[2]);

    return 0;
}