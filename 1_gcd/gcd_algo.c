#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

typedef struct
{
    int gcd;
    int count;
} gcd_result;

gcd_result gcdEuclid(int m, int n)
{
    gcd_result res = {0, 0};
    while (n)
    {
        res.count++;
        int r = m % n;
        m = n;
        n = r;
    }
    res.gcd = m;
    return res;
}

gcd_result gcdConsectiveIntegerChecking(int m, int n)
{
    gcd_result res = {0, 0};

    for (int i = min(m, n); i >= 1; i--)
    {
        res.count++;
        if (m % i == 0 && n % i == 0)
        {
            res.count++;
            res.gcd = i;
            break;
        }
    }
    return res;
}

gcd_result gcdModifiedEuclid(int m, int n)
{
    gcd_result res = {0, 0};
    while (m != n)
    {
        m > n ? (m = m - n) : (n = n - m);
        res.count++;
    }
    res.gcd = m;
    return res;
}