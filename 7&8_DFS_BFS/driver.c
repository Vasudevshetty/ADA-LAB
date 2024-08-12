#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traversals.c"

void plotter(char *traversalType)
{
    char filename[100];
    sprintf(filename, "data/%s_result.dat", traversalType);
    FILE *data = fopen(filename, "w");
    fprintf(data, "#size best worst\n");

    for (int v = 1; v <= 10; v++)
    {
        Graph g;
        initGraph(&g, v);

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                g.adjMatrix[i][j] = (i != j) ? 1 : 0;

        resetGraph(&g);
        strcmp(traversalType, "bfs") == 0 ? bfs(&g, 0) : dfs(&g, 0, -1);
        int bestCase = strcmp(traversalType, "bfs") == 0 ? bfsCount : dfsCount;

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                g.adjMatrix[i][j] = 0;
        for (int i = 0; i < v - 1; i++)
            g.adjMatrix[i][i + 1] = 1;

        resetGraph(&g);
        strcmp(traversalType, "bfs") == 0 ? bfs(&g, 0) : dfs(&g, 0, -1);
        int worstCase = strcmp(traversalType, "bfs") == 0 ? bfsCount : dfsCount;

        fprintf(data, "%d %d %d\n", v, bestCase, worstCase);
        freeGraph(&g);
    }
    fclose(data);
}

void test(char *traversalType)
{
    Graph g;
    int n;
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    initGraph(&g, n);

    printf("Enter the adjacency matrix\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g.adjMatrix[i][j]);

    resetGraph(&g);
    printf("%cFS traversal: ", strcmp(traversalType, "dfs") == 0 ? 'D' : 'B');
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            g.componentCount++;
            strcmp(traversalType, "dfs") == 0 ? dfs(&g, i, -1) : bfs(&g, i);
        }
    }
    printf("%s\n", strcmp(traversalType, "dfs") == 0 ? g.dfsTraversal : g.bfsTraversal);

    printf("The graph is %s\n", g.isCyclic ? "cyclic" : "acyclic");
    printf("The graph is %sconnected\n", g.componentCount == 1 ? "" : "not ");
    printf("The no of components in the graph is %d\n", g.componentCount);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s [test|plot] <type>\n");
        printf("type: 'dfs' | 'bfs'\n");
        exit(1);
    }

    if (strcmp(argv[1], "test") == 0)
        test(argv[2]);
    if (strcmp(argv[1], "plot") == 0)
        plotter(argv[2]);

    return 0;
}