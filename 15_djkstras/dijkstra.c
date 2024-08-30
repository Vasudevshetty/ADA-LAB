#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct vertex
{
    int id, distance;
} vertex;

int distance[10], removed[10] = {0};
int heapOperation = 0, graphOperation = 0;
int n, cost[10][10];
int source, heapsize = 0;

void swap(vertex *a, vertex *b)
{
    vertex temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(vertex heap[], int n, int i)
{
    int lowest = i, left = 2 * i + 1, right = 2 * i + 2;
    heapOperation++;

    if (left < n && heap[left].distance < heap[lowest].distance)
        lowest = left;
    if (right < n && heap[right].distance < heap[lowest].distance)
        lowest = right;

    if (lowest != i)
    {
        swap(&heap[i], &heap[lowest]);
        heapify(heap, n, lowest);
    }
}

void buildHeap(vertex heap[], int n)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(heap, n, i);
}

vertex deleteMin(vertex heap[])
{
    vertex min = heap[0];
    heap[0] = heap[heapsize - 1];
    heapsize--;
    heapify(heap, heapsize, 0);
    return min;
}

void makeGraph()
{
    printf("Enter the no of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (i != j && cost[i][j] == 0)
                cost[i][j] = INT_MAX;
        }
    }

    printf("Enter the source : ");
    scanf("%d", &source);

    for (int i = 0; i < n; i++)
        distance[i] = INT_MAX;
    distance[source] = 0;
}

void dijkstra(vertex heap[])
{
    for (int i = 0; i < n; i++)
    {
        heap[i].id = i;
        heap[i].distance = distance[i];
    }

    heapsize = n;
    buildHeap(heap, heapsize);

    while (heapsize > 0)
    {
        vertex min = deleteMin(heap);
        int u = min.id;
        removed[u] = 1;

        for (int ver = 0; ver < n; ver++)
        {
            if (cost[u][ver] != INT_MAX && !removed[ver])
            {
                graphOperation++;
                if (cost[u][ver] + distance[u] < distance[ver])
                {
                    distance[ver] = cost[u][ver] + distance[u];

                    for (int heapIdx = 0; heapIdx < heapsize; heapIdx++)
                    {
                        if (heap[heapIdx].id == ver)
                        {
                            heap[heapIdx].distance = distance[ver];
                            break;
                        }
                    }
                    buildHeap(heap, heapsize);
                }
            }
        }
    }
}

void run()
{
    makeGraph();
    heapOperation = 0;
    graphOperation = 0;

    vertex heap[10];
    dijkstra(heap);
    printf("The min distance from source %d are,\n", source);
    for (int i = 0; i < n; i++)
    {
        if (i != source)
            printf("%d => %d\n", i, distance[i]);
    }
    printf("The count is %d\n", heapOperation > graphOperation ? heapOperation : graphOperation);
}

int main()
{
    run();
    return 0;
}