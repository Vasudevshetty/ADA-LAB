import java.io.FileWriter;
import java.io.IOException;

public class Plotter {
    public static void plot(String traversalType, String caseType) throws IOException {
        try (FileWriter writer = new FileWriter("./data/" + traversalType + "_data.dat")) {
            for (int v = 1; v <= 10; v++) {
                int[][] adjacencyMatrix = new int[v][v];
                if (caseType.equals("best")) {
                    for (int i = 0; i < v - 1; i++)
                        adjacencyMatrix[i][i + 1] = 1;
                } else if (caseType.equals("worst")) {
                    for (int i = 0; i < v; i++)
                        for (int j = 0; j < v; j++)
                            if (i != j)
                                adjacencyMatrix[i][j] = 1;

                }

                for (int i = 0; i < v; i++) {
                    for (int j = 0; j < v; j++)
                        System.out.print(adjacencyMatrix[i][j] + " ");
                    System.out.println();
                }

                Graph graph = new Graph(adjacencyMatrix);
                graph.bfs(0);

                writer.write(v + "\n");
            }
        }
    }

    public static void main(String[] args) throws IOException{
        plot("bfs", "best");
        plot("bfs", "worst");
    }
}
