#ifndef TRAVERSALS_H
#define TRAVERSALS_H

typedef struct
{
    int **adjMatrix;
    int numVertices;
    int isCyclic;
    int componentCount;
    char bfsTraversal[100];
    char dfsTraversal[100];
} Graph;

void initGraph(Graph *g, int n);
void freeGraph(Graph *g);
void dfs(Graph *g, int start, int parent);
void bfs(Graph *g, int start);
void resetGraph(Graph *g);

#endif