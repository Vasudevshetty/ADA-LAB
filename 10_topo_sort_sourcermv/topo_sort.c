#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int **adjMatrix;
    int numVertices;
    char topoSort[100];
    int indegree[100];
} Graph;

static int stack[100], top = -1;
static int countVertex = 0;

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
    memset(g->topoSort, 0, sizeof(g->topoSort));
    memset(g->indegree, 0, sizeof(g->indegree));
    top = -1;
    countVertex = 0;
}

void calculateIndegree(Graph *g)
{
    for (int i = 0; i < g->numVertices; i++)
    {
        int sum = 0;
        for (int j = 0; j < g->numVertices; j++)
        {
            if (g->adjMatrix[j][i] == 1)
                sum += g->adjMatrix[j][i];
        }
        g->indegree[i] = sum;
    }
}

int topoSort(Graph *g)
{
    int count = 0;
    calculateIndegree(g);

    for (int i = 0; i < g->numVertices; i++)
    {
        if (g->indegree[i] == 0)
            stack[++top] = i;
    }

    int k = 0;
    while (top != -1)
    {
        countVertex++;
        int vertex = stack[top--];
        char vertexLabel[5];
        sprintf(vertexLabel, "%c ", vertex + 65);
        strcat(g->topoSort, vertexLabel);

        for (int i = 0; i < g->numVertices; i++)
        {
            count++;
            if (g->adjMatrix[vertex][i] == 1)
            {
                g->indegree[i]--;
                if (g->indegree[i] == 0)
                    stack[++top] = i;
            }
        }
    }
    return count;
}

void tester()
{
    Graph g;
    int n;
    printf("Enter the no of vertices: ");
    scanf("%d", &n);

    initGraph(&g, n);

    printf("Enter the adjacency matrix\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g.adjMatrix[i][j]);

    topoSort(&g);

    if (countVertex != n)
        printf("The graph has a cycle, topo sort doesn't exist\n");
    else
        printf("The topological order is: %s\n", g.topoSort);

    freeGraph(&g);
}

void plotter()
{
    FILE *data = fopen("topo_sort_results.dat", "w");
    fprintf(data, "#size best worst\n");

    for (int v = 1; v <= 20; v++)
    {
        Graph g;
        initGraph(&g, v);

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                g.adjMatrix[i][j] = (i != j) ? 1 : 0;

        resetGraph(&g);
        int bestCase = topoSort(&g);

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                g.adjMatrix[i][j] = 0;
        for (int i = 0; i < v - 1; i++)
            g.adjMatrix[i][i + 1] = 1;

        resetGraph(&g);
        int worstCase = topoSort(&g);
        fprintf(data, "%d %d %d\n", v, bestCase, worstCase);

        freeGraph(&g);
    }

    fclose(data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <test|plot>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "test") == 0)
        tester();
    else if (strcmp(argv[1], "plot") == 0)
        plotter();
}