#ifndef SORTING_H
#define SORTING_H

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int insertionSort(int *array, int n)
{
    int count = 0;
    for (int i = 1; i < n; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            count++;
            array[j + 1] = array[j];
            j--;
        }
        count++;
        array[j + 1] = key;
    }
    return count;
}

int selectionSort(int *array, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            count++;
            if (array[j] < array[minIdx])
                minIdx = i;
        }

        if (minIdx != i)
            swap(&array[minIdx], &array[i]);
    }
    return count;
}

int bubbleSort(int *array, int n)
{
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int flag = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            count++;
            if (array[j] > array[j + 1])
            {
                flag = 1;
                swap(&array[j], &array[j + 1]);
            }
        }
        if (flag == 0)
            break;
    }
    return count;
}

#endif