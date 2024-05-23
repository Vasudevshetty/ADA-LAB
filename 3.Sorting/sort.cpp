#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <random>
using namespace std;

#define MIN 10
#define MAX 1000

vector<int> generateRandomArray(int size, int minVal, int maxVal, bool unique = false)
{
    vector<int> array;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(minVal, maxVal);

    if (unique)
    {
        if (maxVal - minVal + 1 < size)
        {
            cerr << "Range too small for the size of the array with unique elements";
            return array;
        }

        vector<int> pool;
        for (int i = minVal; i <= maxVal; i++)
            pool.push_back(i);

        shuffle(pool.begin(), pool.end(), gen);
        array.assign(pool.begin(), pool.begin() + size);
    }
    else
    {
        for (int i = 0; i < size; i++)
            array.push_back(distr(gen));
    }
    return array;
}

pair<vector<int>, int> bubbleSort(vector<int> array)
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

pair<vector<int>, int> insertionSort(vector<int> array)
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

pair<vector<int>, int> selectionSort(vector<int> array)
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
    ofstream dataFile("../data/sort_data.dat");
    if (!dataFile.is_open())
    {
        cerr << "Unable to open the file to write";
        return -1;
    }

    dataFile << "# input size | bubble sort | insertion sort | selection sort" << endl;

    for (int size = 100; size <= 1000; size += 100)
    {
        int bubble_count = bubbleSort(generateRandomArray(size, MIN, MAX)).second;
        int insertion_count = insertionSort(generateRandomArray(size, MIN, MAX)).second;
        int selection_count = bubbleSort(generateRandomArray(size, MIN, MAX)).second;

        dataFile << size << " " << bubble_count << " " << insertion_count << " " << selection_count << " " << endl;
    }
    dataFile.close();
    return 0;
}