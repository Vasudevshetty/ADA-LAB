#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int count = 0;
int createCount, deleteCount;

void heapify(int *heap, int n, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n)
    {
        count++;
        if (heap[left] > heap[largest])
            largest = left;
    }

    if (right < n)
    {
        count++;
        if (heap[right] > heap[largest])
            largest = right;
    }

    if (largest != root)
    {
        swap(&heap[root], &heap[largest]);
        heapify(heap, n, largest);
    }
}

int heapSort(int *heap, int n)
{
    count = 0;
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(heap, n, i);
    createCount = count;

    count = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&heap[0], &heap[i]);
        heapify(heap, i, 0);
    }
    deleteCount = count;

    return createCount > deleteCount ? createCount : deleteCount;
}

void tester()
{
    int n;
    printf("Enter the size of the arrray: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array, \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    heapSort(arr, n);

    printf("The elements after sorting are, \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

void plotter()
{
    FILE *data = fopen("heap_sort_results.dat", "w");
    fprintf(data, "#size best average worst\n");

    for (int n = 100; n <= 1000; n += 100)
    {
        int *arr = (int *)malloc(sizeof(int) * (n + 1));

        for (int i = 0; i < n; i++)
            arr[i] = n - i + 1;
        int bestcase = heapSort(arr, n);

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        int worstcase = heapSort(arr, n);

        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        int averagecase = heapSort(arr, n);

        fprintf(data, "%d %d %d %d\n", n, bestcase, averagecase, worstcase);
    }
    fclose(data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <test|plot>\n", argv[0]);
        return -1;
    }

    if (!strcmp(argv[1], "test"))
        tester();
    if (!strcmp(argv[1], "plot"))
        plotter();

    return 0;
}