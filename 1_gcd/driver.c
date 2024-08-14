#include <stdio.h>
#include <stdlib.h>
#include "gcd_algo.c"
#include <string.h>

typedef gcd_result (*gcd_func)(int, int);

gcd_func get_gcd_func(char *gcdType)
{
    if (!strcmp(gcdType, "euclid"))
        return gcdEuclid;
    if (!strcmp(gcdType, "modified"))
        return gcdModifiedEuclid;
    if (!strcmp(gcdType, "consective"))
        return gcdConsectiveIntegerChecking;

    return NULL;
}

void plotter(char *gcdType)
{
    char filename[250];
    sprintf(filename, "data/%s_results.dat", gcdType);
    gcd_func gcd_algo = get_gcd_func(gcdType);

    FILE *data = fopen(filename, "w");
    fprintf(data, "#size best worst\n");

    for (int i = 10; i <= 100; i += 10)
    {
        int m, n;
        int algo_min = 10000, algo_max = 0;

        for (int j = 2; j <= i; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                m = j, n = k;
                gcd_result res = gcd_algo(m, n);
                if (res.count > algo_max)
                    algo_max = res.count;
                if (res.count < algo_min)
                    algo_min = res.count;
            }
        }

        fprintf(data, "%d %d %d\n", m, algo_min, algo_max);
    }

    fclose(data);
}

void test(char *gcdType)
{
    int m, n;
    printf("Enter m & n: ");
    scanf("%d %d", &m, &n);
    gcd_func gcd_algo = get_gcd_func(gcdType);

    gcd_result res = gcd_algo(m, n);

    printf("The gcd of %d and %d is %d\n", m, n, res.gcd);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: <plot|test> <type>\n");
        printf("type: <euclid|modified|consective>\n");
        return 1;
    }

    if (!strcmp(argv[1], "test"))
        test(argv[2]);
    if (!strcmp(argv[1], "plot"))
        plotter(argv[2]);

    return 0;
}