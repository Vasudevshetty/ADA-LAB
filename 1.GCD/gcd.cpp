#include <bits/stdc++.h>
using namespace std;

#define MIN 0
#define MAX 10

pair<int, int> gcdEuclid(int m, int n);
pair<int, int> gcdConsecutiveIntegerChecking(int m, int n);
pair<int, int> gcdModifiedEuclid(int m, int n);

/*Implement Euclid's consecutive integer checking and modified Euclid's algorithms to find GCD of two non negative integers and perform compartive analysis.*/

void preProcessData(const string &inputFile, const string &outputFile)
{
    ifstream dataFile(inputFile);
    ofstream processedFile(outputFile);

    if (!dataFile.is_open() || !processedFile.is_open())
    {
        cerr << "Unable to open the file" << endl;
        return;
    }

    vector<array<int, 4>> data;
    string line;

    getline(dataFile, line);

    while (getline(dataFile, line))
    {
        stringstream ss(line);
        int m, n, gcd, euclid, consecutive, modified;
        ss >> m >> n >> gcd >> euclid >> consecutive >> modified;
        data.push_back({m, euclid, consecutive, modified});
    }

    processedFile << "# m  min_euclid max_euclid min_consecutive max_consecutive min_modified max_modified\n";
    for (size_t i = 0; i < data.size(); i += 10)
    {
        int min_euclid = INT_MAX, max_euclid = INT_MIN;
        int min_consecutive = INT_MAX, max_consecutive = INT_MIN;
        int min_modified = INT_MAX, max_modified = INT_MIN;

        for (size_t j = i; j < i + 10 && j < data.size(); ++j)
        {
            min_euclid = min(min_euclid, data[j][3]);
            max_euclid = max(max_euclid, data[j][3]);
            min_consecutive = min(min_consecutive, data[j][4]);
            max_consecutive = max(max_consecutive, data[j][4]);
            min_modified = min(min_modified, data[j][5]);
            max_modified = max(max_modified, data[j][5]);
        }

        processedFile << data[i][0] << " "
                      << min_euclid << " " << max_euclid << " "
                      << min_consecutive << " " << max_consecutive << " "
                      << min_modified << " " << max_modified << "\n";
    }
    dataFile.close();
    processedFile.close();
}

int main()
{
    ofstream dataFile("../data/gcd_counts.dat");

    if (!dataFile.is_open())
    {
        cerr << "Unable to open the file for writing" << endl;
        return 1;
    }

    dataFile << "# GCD  | euclid | consective | modified \n";

    for (int i = MIN; i <= MAX; i += 10)
    {
        for (int j = 2; j <= i; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                int m = j, n = k;
                auto resultEuclid = gcdEuclid(m, n);
                auto resultConsecutive = gcdConsecutiveIntegerChecking(m, n);
                auto resultModifiedEuclid = gcdModifiedEuclid(m, n);

                int gcd = resultEuclid.first;

                /*
                printf("Gcd of %d and %d is %d\n", m, n, gcd);
                printf("The Count taken is %d %d %d\n", resultEuclid.second, resultConsecutive.second, resultModifiedEuclid.second);
                */

                dataFile << m << " "
                         << n << " " << gcd
                         << " "
                         << resultEuclid.second << " "
                         << resultConsecutive.second << " "
                         << resultModifiedEuclid.second << endl;
            }
        }
    }
    dataFile.close();

    preProcessData("../data/gcd_counts.dat", "../data/gcd_processed_counts.dat");

    return 0;
}

pair<int, int> gcdEuclid(int m, int n)
{
    int count = 0;
    while (n)
    {
        count++;
        int r = m % n;
        m = n;
        n = r;
    }
    count++;
    return {m, count};
}

pair<int, int> gcdConsecutiveIntegerChecking(int m, int n)
{
    int count = 0, gcd = 1;
    for (int i = min(m, n); i >= 1; i--)
    {
        count++;
        if (m % i == 0 && n % i == 0)
        {
            count++;
            gcd = i;
            break;
        }
    }
    return {gcd, count};
}

pair<int, int> gcdModifiedEuclid(int m, int n)
{
    int count = 0;
    while (m != n)
    {
        m > n ? (m = m - n) : (n = n - m);
        count++;
    }
    count++;
    return {m, count};
}
