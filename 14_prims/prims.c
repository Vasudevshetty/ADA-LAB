#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Edge
{
    int source;
    int destination;
    int weight;
} Edge;

Edge mst[10];
int heapOperation = 0, graphOperation = 0;
int n, cost[10][10];
int heapsize = 0;

void swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Edge heap[], int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    heapOperation++;

    if (left < heapsize && heap[left].weight < heap[smallest].weight)
        smallest = left;

    if (right < heapsize && heap[right].weight < heap[smallest].weight)
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[smallest], &heap[i]);
        heapify(heap, smallest);
    }
}

void buildHeap(Edge heap[])
{
    for (int i = (heapsize / 2) - 1; i >= 0; i--)
        heapify(heap, i);
}

Edge deleteMinEdgeFromHeap(Edge heap[])
{
    Edge minEdge = heap[0];
    heap[0] = heap[--heapsize]; // Update heapsize globally
    heapify(heap, 0);           // Fix the heap property
    return minEdge;
}

void prim()
{
    Edge heap[10];
    int visited[10] = {0}; // Initialize visited array to 0
    int removed[10] = {0}; // Initialize removed array to 0

    visited[0] = 1;
    heap[heapsize++] = (Edge){0, -1, 0};

    for (int vertex = 0; vertex < n - 1; vertex++)
    {
        Edge minEdge = deleteMinEdgeFromHeap(heap);

        if (minEdge.destination != -1)
            mst[vertex] = minEdge;

        int source = minEdge.source;
        removed[source] = 1;

        for (int target = 0; target < n; target++)
        {
            graphOperation++;

            if (!visited[target] && cost[source][target] != INT_MAX && !removed[target])
            {
                visited[target] = 1;
                heap[heapsize++] = (Edge){source, target, cost[source][target]};
            }

            if (visited[target] && cost[source][target] != INT_MAX && !removed[target])
            {
                for (int heapIndex = 0; heapIndex < heapsize; heapIndex++)
                {
                    if (heap[heapIndex].destination == target && cost[source][target] < heap[heapIndex].weight)
                    {
                        heap[heapIndex].weight = cost[source][target];
                        heap[heapIndex].source = source;
                        break;
                    }
                }
            }
        }
        buildHeap(heap);
    }
}

void makeGraph()
{
    printf("Enter total number of vertices: ");
    scanf("%d", &n);
    printf("Enter the cost matrix of the graph:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (i != j && cost[i][j] == 0) // Only replace 0 with INT_MAX if it's not on the diagonal
                cost[i][j] = INT_MAX;
        }
    }
}

void run(int plot)
{
    int sum = 0;
    makeGraph();
    prim();

    for (int i = 0; i < n - 1; i++)
    {
        printf("%c -> %c == %d\n", mst[i].source + 'A', mst[i].destination + 'A', mst[i].weight);
        sum += mst[i].weight;
    }

    printf("Minimum distance is %d\n", sum);

    if (plot)
    {
        FILE *data = fopen("prims_results.dat", "a");
        if (data != NULL)
        {
            fprintf(data, "#size count\n");
            int maxCount = heapOperation > graphOperation ? heapOperation : graphOperation;
            fprintf(data, "%d %d\n", n, maxCount);
            fclose(data); // Close the file after writing
        }
        else
        {
            printf("Error opening file for writing.\n");
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    { // Corrected to check if there's at least one argument after the program name
        printf("Usage: <test|plot>\n");
        return -1;
    }

    if (!strcmp(argv[1], "test"))
        run(0);
    else if (!strcmp(argv[1], "plot"))
        run(1);
    else
        printf("Invalid argument: %s\nUsage: <test|plot>\n", argv[1]);

    return 0;
}
