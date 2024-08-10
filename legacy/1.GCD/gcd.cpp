#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

#define MIN 10
#define MAX 100

pair<int, int> gcdEuclid(int m, int n);
pair<int, int> gcdConsecutiveIntegerChecking(int m, int n);
pair<int, int> gcdModifiedEuclid(int m, int n);

/*Implement Euclid's consecutive integer checking and modified Euclid's algorithms to find GCD of two non negative integers and perform compartive analysis.*/

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
        int m, n;
        int min_euclid = 10000, max_euclid = 0;
        int min_consecutive = 10000, max_consecutive = 0;
        int min_modified = 10000, max_modified =0;
        for (int j = 2; j <= i; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                m = j, n = k;
                auto resultEuclid = gcdEuclid(m, n);
                auto resultConsecutive = gcdConsecutiveIntegerChecking(m, n);
                auto resultModifiedEuclid = gcdModifiedEuclid(m, n);

                /*
                printf("Gcd of %d and %d is %d\n", m, n, gcd);
                printf("The Count taken is %d %d %d\n", resultEuclid.second, resultConsecutive.second, resultModifiedEuclid.second);
                */

                min_euclid = min(min_euclid, resultEuclid.second);
                max_euclid = max(max_euclid, resultEuclid.second);
                min_consecutive = min(min_consecutive, resultConsecutive.second);
                max_consecutive = max(max_consecutive, resultConsecutive.second);
                min_modified = min(min_modified, resultModifiedEuclid.second);
                max_modified = max(max_modified, resultModifiedEuclid.second);
            }
        }
        dataFile << m << " "
                 << min_euclid << " " << max_euclid << " "
                 << min_consecutive << " " << max_consecutive << " "
                 << min_modified << " " << max_modified << "\n";
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
