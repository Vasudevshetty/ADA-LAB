#ifndef SEARCHING_H
#define SEARCHING_H

typedef struct
{
    int count, index;
} searchResult;

searchResult linearSearch(int *array, int n, int key)
{
    searchResult result = {0, -1};

    for (int i = 0; i < n; i++)
    {
        result.count++;
        if (array[i] == key)
        {
            result.index = i;
            break;
        }
    }
    return result;
}

searchResult binarySearchRecursive(int *array, int low, int high, int key, int count)
{
    searchResult result = {count, -1};

    if (low <= high)
    {
        int mid = low + (high - low) / 2;
        result.count++;
        if (array[mid] == key)
        {
            result.index = mid;
            return result;
        }
        else if (array[mid] < key)
            return binarySearchRecursive(array, mid + 1, high, key, result.count);
        else
            return binarySearchRecursive(array, low, mid - 1, key, result.count);
    }
    return result;
}

searchResult binarySearch(int *array, int n, int key)
{
    return binarySearchRecursive(array, 0, n - 1, key, 0);
}

#endif