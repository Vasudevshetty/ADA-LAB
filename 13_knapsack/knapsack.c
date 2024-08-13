#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int t[100][100], v[100], w[100];
int count = 0;

int max(int a, int b) { return a > b ? a : b; }

int knap(int n, int m)
{
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m + 1; j++)
        {
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else
            {
                count++;
                if (j < w[i - 1])
                    t[i][j] = t[i - 1][j];
                else
                    t[i][j] = max(t[i - 1][j], v[i - 1] + t[i - 1][j - w[i - 1]]);
            }
        }
    }

    return t[n][m];
}

int knapMemoized(int i, int j)
{
    count++;
    if (t[i][j] == -1)
    {
        if (j < w[i - 1])
            t[i][j] = knapMemoized(i - 1, j);
        else
            t[i][j] = max(knapMemoized(i - 1, j), v[i - 1] + knapMemoized(i - 1, j - w[i - 1]));
    }

    return t[i][j];
}

void run(int memoized)
{
    FILE *data = fopen("knapsack_result.dat", "a");

    int n, m;
    printf("Enter no of items: ");
    scanf("%d", &n);

    printf("Enter sack capacity: ");
    scanf("%d", &m);

    printf("Enter weight and value\nWeight\tValue\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &w[i], &v[i]);

    count = 0;

    if (memoized)
    {
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < m + 1; j++)
                t[i][j] = i == 0 || j == 0 ? 0 : -1;
    }

    printf("The max value of the knapsack is %d\n", memoized == 0 ? knap(n, m) : knapMemoized(n, m));

    printf("The obtained cost matrix\n");
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m + 1; j++)
            printf("%d ", t[i][j]);
        printf("\n");
    }

    printf("Composition, the items selected are\n");
    int capacity = m;
    for (int i = n; i >= 0; i--)
    {
        if (t[i][capacity] != t[i - 1][capacity])
        {
            printf("%d\t", i);
            capacity -= w[i];
        }
    }
    printf("\n");

    fprintf(data, "%d %d\n", n, count);

    fclose(data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: <memoized|normal> <test|plot>\n");
        return 1;
    }

    if (strcmp(argv[1], "test") == 0)
        run(strcmp(argv[2], "memoized") == 0 ? 1 : 0);
    if (strcmp(argv[1], "plot") == 0)
        for (int i = 0; i < 4; i++)
            run(strcmp(argv[2], "memoized") == 0 ? 1 : 0);

    return 0;
}