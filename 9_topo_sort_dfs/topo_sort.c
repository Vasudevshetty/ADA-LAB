#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int visited[100];
static int stack[100], top = -1;
static int count = 0;

typedef struct
{
    int **adjMatrix;
    int numVertices;
    char topoSort[100];
} Graph;

void initGraph(Graph *g, int n)
{
    g->numVertices = n;
    memset(g->topoSort, 0, sizeof(g->topoSort));
    g->adjMatrix = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        g->adjMatrix[i] = (int *)malloc(sizeof(int) * n);
}

void freeGraph(Graph *g)
{
    for (int i = 0; i < g->numVertices; i++)
        free(g->adjMatrix[i]);
    free(g->adjMatrix);
}

void resetGraph(Graph *g)
{
    memset(visited, 0, sizeof(visited));
    memset(g->topoSort, 0, sizeof(g->topoSort));
    top = -1;
    count = 0;
}

void dfs(Graph *g, int start)
{
    visited[start] = 1;
    for (int i = 0; i < g->numVertices; i++)
    {
        count++;
        if (g->adjMatrix[start][i] && visited[i] == 0)
            dfs(g, i);
    }
    stack[++top] = start;
}

void topoSort(Graph *g)
{
    for (int i = 0; i < g->numVertices; i++)
        if (visited[i] == 0)
            dfs(g, i);

    while (top != -1)
    {
        char vertexLabel[5];
        sprintf(vertexLabel, "%c ", stack[top--] + 65);
        strcat(g->topoSort, vertexLabel);
    }
}

void test()
{
    Graph g;
    int n;
    printf("Enter the number of nodes in the grpah: ");
    scanf("%d", &n);

    initGraph(&g, n);
    printf("Enter the adj Matrix\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g.adjMatrix[i][j]);

    resetGraph(&g);
    topoSort(&g);
    printf("Topological Sorting: %s\n", g.topoSort);
}

void plotter()
{
    FILE *data = fopen("topo_sort_results.dat", "w");
    fprintf(data, "#size best worst\n");

    for (int v = 1; v <= 10; v++)
    {
        Graph g;
        initGraph(&g, v);

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                g.adjMatrix[i][j] = (i != j) ? 1 : 0;

        resetGraph(&g);
        topoSort(&g);
        int bestCase = count;

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                g.adjMatrix[i][j] = 0;
        for (int i = 0; i < v - 1; i++)
            g.adjMatrix[i][i + 1] = 1;

        resetGraph(&g);
        topoSort(&g);
        int worstCase = count;

        fprintf(data, "%d %d %d\n", v, bestCase, worstCase);
        freeGraph(&g);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <test|plot>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "test") == 0)
        test();
    if (strcmp(argv[1], "plot") == 0)
        plotter();

    return 0;
}