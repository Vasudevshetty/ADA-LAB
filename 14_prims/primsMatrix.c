#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minKey(int key[], int mstSet[], int n)
{
    int min = INT_MAX, min_idx;
    for (int v = 0; v < n; v++)
    {
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_idx = v;
    }
    return min_idx;
}

void printMst(int parent[], int graph[10][10], int n)
{
    int cost = 0;
    printf("Edge Weight\n");
    for (int i = 1; i < n; i++)
    {
        cost += graph[i][parent[i]];
        printf("%d - %d  %d\n", parent[i], i, graph[i][parent[i]]);
    }
    printf("The total cost is %d\n", cost);
}

void prims(int graph[10][10], int n)
{
    int parent[10], key[10], mstSet[10];

    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int vertex = 0; vertex < n - 1; vertex++)
    {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
        }
    }
    printMst(parent, graph, n);
}

int main()
{
    int n;
    int graph[10][10];
    printf("Enter the n: ");
    scanf("%d", &n);
    printf("The matrix\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    prims(graph, n);
    return 0;
}