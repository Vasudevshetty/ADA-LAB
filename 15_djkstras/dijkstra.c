#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int heapOperation = 0, graphOperation = 0;
int n, cost[10][10], heapsize = 0;
int distance[10], removed[10];
int source;

typedef struct vertex {
    int id;
    int distance;
} vertex;

void swap(vertex *a, vertex *b) {
    vertex temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(vertex heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    heapOperation++;

    if (left < n && heap[left].distance < heap[smallest].distance)
        smallest = left;
    if (right < n && heap[right].distance < heap[smallest].distance)
        smallest = right;

    if (smallest != i) {
        swap(&heap[smallest], &heap[i]);
        heapify(heap, n, smallest);
    }
}

void buildHeap(vertex heap[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(heap, n, i);
}

vertex deleteMin(vertex heap[]) {
    vertex min = heap[0];
    heap[0] = heap[heapsize - 1];
    heapsize--;
    heapify(heap, heapsize, 0);
    return min;
}

void makeGraph() {
    printf("Enter the total number of vertices: ");
    scanf("%d", &n);
    printf("Enter the cost matrix of the graph,\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INT_MAX;
        }
    }

    printf("Enter the source vertex (0-based index): ");
    scanf("%d", &source);

    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        removed[i] = 0;
    }
    distance[source] = 0;
}

void dijkstra(vertex heap[]) {
    for (int i = 0; i < n; i++) {
        heap[i].id = i;
        heap[i].distance = INT_MAX;
    }

    heap[source].distance = 0;
    heapsize = n;

    buildHeap(heap, heapsize);

    while (heapsize > 0) {
        vertex min = deleteMin(heap);
        int u = min.id;
        removed[u] = 1;

        for (int ver = 0; ver < n; ver++) {
            if (cost[u][ver] != INT_MAX && !removed[ver]) {
                graphOperation++;
                if (distance[u] + cost[u][ver] < distance[ver]) {
                    distance[ver] = distance[u] + cost[u][ver];
                    // Update the heap
                    for (int heapIdx = 0; heapIdx < heapsize; heapIdx++) {
                        if (heap[heapIdx].id == ver) {
                            heap[heapIdx].distance = distance[ver];
                            break;
                        }
                    }
                    buildHeap(heap, heapsize); // Rebuild the heap to reflect changes
                }
            }
        }
    }
}

void run(int plot) {
    makeGraph();
    graphOperation = 0;
    heapOperation = 0;

    vertex heap[10];
    dijkstra(heap);

    printf("Shortest path from vertex %d:\n", source);
    for (int i = 0; i < n; i++) {
        if (source != i) {
            if (distance[i] == INT_MAX)
                printf("%d -> %d = INF\n", source, i);
            else
                printf("%d -> %d = %d\n", source, i, distance[i]);
        }
    }

    int count = graphOperation > heapOperation ? graphOperation : heapOperation;
    if (plot) {
        FILE *data = fopen("dijkstra_results.dat", "a");
        if (data != NULL) {
            fprintf(data, "#size count\n");
            fprintf(data, "%d %d\n", n, count);
            fclose(data);
        } else {
            printf("Error opening file for writing.\n");
        }
    }
    printf("Operation count = %d\n", count);
}

int main() {
    run(1);
    return 0;
}

