#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int graph[100][100];

int warshall(int n)
{
    int count = 0;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (graph[i][k] != 0)
            {
                for (int j = 0; j < n; j++)
                {
                    graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
                    count++;
                }
            }
        }
    }
    return count;
}

void plotter()
{
    FILE *data = fopen("data/warshall_results.dat", "w");
    fprintf(data, "#size best worst\n");

    for (int n = 2; n <= 10; n++)
    {

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j) ? 1 : 0;

        int bestCase = warshall(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
            graph[i][i + 1] = 1;

        int worstCase = warshall(n);

        fprintf(data, "%d %d %d\n", n, bestCase, worstCase);
    }
    fclose(data);
}

void test()
{
    int n;
    printf("Enter the no of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix \n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    warshall(n);
    printf("The transitive clousure graph is \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: <plot|test>\n");
        return 1;
    }

    if (strcmp(argv[1], "test") == 0)
        test();
    if (strcmp(argv[1], "plot") == 0)
        plotter();

    return 0;
}
