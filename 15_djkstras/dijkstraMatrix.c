#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

int minDistance(int dist[], int visited[], int n)
{
    int min_index, min = INF;
    for (int v = 0; v < n; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

int dijkstra(int graph[10][10], int n, int src)
{
    int dist[10], visited[10];
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int vertex= 0; vertex< n - 1; vertex++)
    {
        int u = minDistance(dist, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            count++;
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < n; i++)
        printf("%d \t\t %d\n", src, dist[i]);

    return count;
}

int main()
{
    int n, src;
    int graph[10][10];

    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Input the graph as an adjacency matrix
    printf("Enter the adjacency matrix (enter 0 for no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    // Input the source vertex
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    // Run Dijkstra's algorithm
    int count = dijkstra(graph, n, src);
    printf("The count is %d\n", count);

    return 0;
}