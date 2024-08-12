#include "traversals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int visited[100];
static int dfsCount = 0;
static int bfsCount = 0;

void initGraph(Graph *g, int n)
{
    g->numVertices = n;
    g->isCyclic = 0;
    g->componentCount = 0;
    memset(g->dfsTraversal, 0, sizeof(g->dfsTraversal));
    memset(g->bfsTraversal, 0, sizeof(g->bfsTraversal));

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
    dfsCount = 0;
    bfsCount = 0;
    g->isCyclic = 0;
    g->componentCount = 0;
    memset(g->dfsTraversal, 0, sizeof(g->dfsTraversal));
    memset(g->bfsTraversal, 0, sizeof(g->bfsTraversal));
}

void dfs(Graph *g, int start, int parent)
{
    visited[start] = 1;

    char vertexLabel[5];
    sprintf(vertexLabel, "%c", start + 65);
    strcat(g->dfsTraversal, vertexLabel);

    for (int i = 0; i < g->numVertices; i++)
    {
        if (i != parent && g->adjMatrix[start][i] == 1 && visited[i])
            g->isCyclic = 1;

        dfsCount++;
        if (g->adjMatrix[start][i] && visited[i] == 0)
            dfs(g, i, start);
    }
}

void bfs(Graph *g, int start)
{
    int queue[100], front = 0, rear = 0, parent[100];
    visited[start] = 1;
    queue[rear++] = start;
    parent[start] = -1;

    while (front != rear)
    {
        int current = queue[front++];
        char vertexLabel[5];
        sprintf(vertexLabel, "%c", 65 + current);
        strcat(g->bfsTraversal, vertexLabel);

        for (int i = 0; i < g->numVertices; i++)
        {
            bfsCount++;
            if (i != parent[current] && g->adjMatrix[current][i] && visited[i])
                g->isCyclic = 1;

            if (g->adjMatrix[current][i] && visited[i] == 0)
            {
                queue[rear++] = i;
                parent[i] = current;
                visited[i] = 1;
            }
        }
    }
}