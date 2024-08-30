#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge
{
    int source;
    int destination;
    int distance;
} edge;

int heapOperation = 0, graphOperation = 0;
int heapsize = 0, vertices = 0;
int cost[10][10], n;
edge mst[10];
int visited[10] = {0}, removed[10] = {0};

void swap(edge *a, edge *b)
{
    edge temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(edge heap[], int n, int i)
{
    int lowest = i, left = 2 * i + 1, right = 2 * i + 2;
    heapOperation++;

    if (left < n && heap[left].distance < heap[lowest].distance)
        lowest = left;
    if (right < n && heap[right].distance < heap[lowest].distance)
        lowest = right;

    if (lowest != i)
    {
        swap(&heap[lowest], &heap[i]);
        heapify(heap, n, lowest);
    }
}

void buildHeap(edge heap[], int heapsize)
{
    for (int i = (heapsize / 2) - 1; i >= 0; i--)
        heapify(heap, heapsize, i);
}

edge deleteMin(edge heap[])
{
    edge min = heap[0];
    heap[0] = heap[heapsize - 1];
    heapsize--;
    heapify(heap, heapsize, 0);
    return min;
}

void makeGraph()
{
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter cost matrix,\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INT_MAX;
        }
    }
}

void prim(edge heap[])
{
    heap[heapsize] = (edge){0, -1, 0};
    heapsize++;

    while (vertices != n)
    {
        edge min = deleteMin(heap);
        mst[vertices] = min;
        vertices++;

        int source = min.source;
        removed[source] = 1;

        for (int vertex = 1; vertex < n; vertex++)
        {
            if (!visited[vertex] && cost[source][vertex] != INT_MAX && !removed[vertex])
            {
                visited[vertex] = 1;
                heap[heapsize++] = (edge){vertex, source, cost[source][vertex]};
            }

            if (visited[vertex] && cost[source][vertex] != INT_MAX && !removed[vertex])
            {
                for (int heapIdx = 0; heapIdx < heapsize; heapIdx++)
                {
                    if (heap[heapIdx].source == vertex && heap[heapIdx].distance > cost[source][vertex])
                    {
                        heap[heapIdx].distance = cost[source][vertex];
                        heap[heapIdx].destination = source;
                        break;
                    }
                }
            }
        }
        buildHeap(heap, heapsize);
    }
}

void run()
{
    makeGraph();
    vertices = 0;
    graphOperation = 0;
    heapOperation = 0;

    edge heap[10];
    prim(heap);

    int sum = 0;
    for (int i = 1; i < vertices; i++)
    {
        printf("%d => %d\n", i, mst[i].distance);
        sum += mst[i].distance;
    }

    printf("The minimum distance is %d\n", sum);
}
int main()
{
    run();
    return 0;
}