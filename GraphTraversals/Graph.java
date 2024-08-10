import java.util.LinkedList;
import java.util.Queue;

public class Graph {
    private int[][] adjacencyMatrix;
    private boolean[] visited;
    private int numVertices;
    public int components;

    public Graph(int[][] adjacencyMatrix) {
        this.adjacencyMatrix = adjacencyMatrix;
        this.numVertices = adjacencyMatrix.length;
        this.visited = new boolean[numVertices];
    }

    public StringBuilder bfs(int start) {
        StringBuilder result = new StringBuilder();
        Queue<Integer> queue = new LinkedList<>();
        queue.add(start);
        visited[start] = true;

        while (!queue.isEmpty()) {
            int vertex = queue.poll();
            result.append("-->" + (char) (vertex + 65));
            for (int i = 0; i < numVertices; i++) {
                if (adjacencyMatrix[vertex][i] != 0 && !visited[i]) {
                    queue.add(i);
                    visited[i] = true;
                }
            }
        }
        return result;
    }

    public StringBuilder bfsAllComponents() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                components++;
                result.append(bfs(i)).append("\n");
            }
        }
        return result;
    }

    public boolean isConnected() {
        for (boolean isVisited : visited)
            if (!isVisited)
                return false;
        return true;
    }
}
