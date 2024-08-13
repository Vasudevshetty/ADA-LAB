#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int inf = INT_MAX;
int graph[40][40];

int floyds(int n)
{
    int count = 0;

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                count++;
                if (graph[i][k] != inf && graph[k][j] != inf)
                {
                    int path = graph[i][k] + graph[k][j];
                    if (path < graph[i][j])
                        graph[i][j] = path;
                }
            }
        }
    }
    return count;
}

void createGraph(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = rand() % 100 + 1;
        }
    }
}

void printGraph(int n)
{
    printf("All pairs shortest path matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == inf)
                printf("INF ");
            else
                printf("%3d ", graph[i][j]);
        }
        printf("\n");
    }
}

void test()
{
    int n;
    printf("Enter the no of vertices: ");
    scanf("%d", &n);
    printf("Enter the matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = inf;
        }
    }

    floyds(n);
    printf("Applying floyds algorithm for n = %d\n", n);
    printGraph(n);
}

void plotter()
{
    FILE *data = fopen("data/floyds_results.dat", "w");
    fprintf(data, "#size general\n");

    for (int n = 2; n < 12; n++)
    {
        createGraph(n);
        int count = floyds(n);

        fprintf(data, "%d %d\n", n, count);
    }

    fclose(data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: <test|plot>\n");
        return 1;
    }

    if (strcmp(argv[1], "test") == 0)
        test();
    if (strcmp(argv[1], "plot") == 0)
        plotter();

    return 0;
}