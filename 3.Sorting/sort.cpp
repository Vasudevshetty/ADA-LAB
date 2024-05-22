#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

pair<vector<int>, int> bubbleSort(vector<int> &array)
{
    int count = 0;
    int n = array.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            count++;
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
        }
    }
    return {array, count};
}

pair<vector<int>, int> insertionSort(vector<int> &array)
{
    int count = 0;
    int n = array.size();
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
        array[j + 1] = key;
    }
    return {array, count};
}

pair<vector<int>, int> selectionSort(vector<int> &array)
{
    int count = 0;
    int n = array.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            count++;
            if (array[j] < array[minIndex])
                minIndex = j;
        }
        swap(array[minIndex], array[i]);
    }
    return {array, count};
}

int main()
{
    vector<int> array({2, 8, 1, 3, 4, 9, 7, 6, 10, 5});
    insertionSort(array);
    for (auto ele : array)
        cout << ele << " ";
    cout << endl;
}