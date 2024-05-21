#include <bits/stdc++.h>
using namespace std;

#define MIN 1
#define MAX 100

pair<int, int> gcdEuclid(int m, int n);
pair<int, int> gcdConsecutiveIntegerChecking(int m, int n);
pair<int, int> gcdModifiedEuclid(int m, int n);

/*Implement Euclid's consecutive integer checking and modified Euclid's algorithms to find GCD of two non negative integers and perform compartive analysis.*/

int generateRandomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

vector<pair<int, int>> generateRandomPairs(int numTests)
{
    vector<pair<int, int>> randomPairs;

    for (int i = 0; i < numTests; i++)
    {
        int m = generateRandomInt(MIN, MAX);
        int n = generateRandomInt(MIN, MAX);
        randomPairs.push_back({m, n});
    }

    return randomPairs;
}

int main()
{
    srand(time(0));

    ofstream dataFile("../data/gcd_counts.dat");

    if (!dataFile.is_open())
    {
        cerr << "Unable to open the file for writing" << endl;
        return 1;
    }

    int numTests;
    cin >> numTests;

    dataFile << "# GCD  | euclid | consective | modified \n";

    for (const auto &testCase : generateRandomPairs(numTests))
    {
        int m = testCase.first, n = testCase.second;
        auto resultEuclid = gcdEuclid(m, n);
        auto resultConsecutive = gcdConsecutiveIntegerChecking(m, n);
        auto resultModifiedEuclid = gcdModifiedEuclid(m, n);

        int gcd = resultEuclid.first;
        printf("Gcd of %d and %d is %d\n", m, n, gcd);
        printf("The Count taken is %d %d %d\n", resultEuclid.second, resultConsecutive.second, resultModifiedEuclid.second);

        dataFile << m << " "
                 << n << " " << gcd
                 << " "
                 << resultEuclid.second << " "
                 << resultConsecutive.second << " "
                 << resultModifiedEuclid.second << endl;
    }

    dataFile.close();
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
