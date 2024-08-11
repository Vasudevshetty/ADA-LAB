#include <stdio.h>
#include <stdlib.h>
#include "searching.h"
#include <string.h>
#include <time.h>

void test(char *searchType)
{
    int n, key;
    printf("Enter n: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements: \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter key: ");
    scanf("%d", &key);
    searchResult result = searchType[0] == 'b' ? binarySearch(arr, n, key) : linearSearch(arr, n, key);
    if (result.index == -1)
        printf("Key not found\n");
    else
        printf("key found at index %d\n", result.index);
}

void plotter(char *searchType)
{
    char filename[250];
    sprintf(filename, "data/%s_results.dat", searchType);

    FILE *data = fopen(filename, "w");
    fprintf(data, "#size best avg worst\n");
    srand(time(NULL));

    for (int n = 2; n <= 1024; n *= 2)
    {
        int *arr = (int *)malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++)
            arr[i] = 1;

        searchResult bestCase, worstCase;
        if (strcmp(searchType, "linear") == 0)
        {
            bestCase = linearSearch(arr, n, 1);
            worstCase = linearSearch(arr, n, 0);
        }
        else
        {
            int mid = (n - 1) / 2;
            arr[mid] = 0;
            bestCase = binarySearch(arr, n, 0);
            worstCase = binarySearch(arr, n, 3);
        }

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        searchResult avgCase = (strcmp(searchType, "linear") == 0) ? linearSearch(arr, n, rand() % n) : binarySearch(arr, n, rand() % n);
        fprintf(data, "%d %d %d %d\n", n, bestCase.count, avgCase.count, worstCase.count);

        free(arr);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <plot|test> <linear|binary>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "plot") == 0)
        plotter(argv[2]);
    if (strcmp(argv[1], "test") == 0)
        test(argv[2]);

    return 0;
}