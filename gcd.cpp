#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if (a == b)
        return a;
    else
        return a > b ? gcd(a - b, b) : gcd(a, b - a);
}

int gcdOptimised(int a, int b)
{
    if (a == b)
        return a;
    else
        return a > b ? gcd(a % b, b) : gcd(a, b % a);
}
