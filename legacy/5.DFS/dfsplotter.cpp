#include <iostream>
#include <fstream>
using namespace std;

struct Node
{
    int info;
    Node *next;

    Node(int info)
    {
        this->info = info;
        this->next = next;
    }
};

struct Graph
{
    int vertices;
    Node **adjList;
    int *visit;

    Graph(int vertices)
    {
        this->vertices = vertices;
        adjList = new Node *[vertices];
        visit = new int[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adjList[i] = nullptr;
            visit[i] = 0;
        }
    }

    ~Graph()
    {
        delete[] adjList;
        delete[] visit;
    }

    void addEdge(int src, int dest)
    {
        Node *newNode = new Node(dest);
        newNode->next = adjList[src];
        adjList[src] = newNode;
    }

    void DFS(int vertex, int parent, int &count, int &gcount, int &iscyclic)
    {
        count++;
        visit[vertex] = 1;
        cout << "--> " << char(vertex + 65) << " ";

        Node *temp = adjList[vertex];
        while (temp != nullptr)
        {
            gcount++;
            int connectVertex = temp->info;
            if (visit[connectVertex] == 1 && connectVertex != parent)
                iscyclic = 1;
            if (visit[connectVertex] == 0)
                DFS(connectVertex, vertex, count, gcount, iscyclic);

            temp = temp->next;
        }
    }

    void plotter(int k)
    {
        ofstream fp1("dfsbest.txt", ios::app);
        ofstream fp2("dfsworst.txt", ios::app);

        for (int i = 1; i <= 10; i++)
        {
            int n = i;
            Graph g(n);

            if (k == 0)
            {
                for (int j = 0; j < g.vertices - 1; j++)
                    g.addEdge(j, j + 1);
            }
            else if (k == 1)
            {
                for (int j = 0; j < g.vertices; j++)
                {
                    for (int l = 0; l < g.vertices; l++)
                    {
                        if (j != g.vertices - l - 1)
                            g.addEdge(j, g.vertices - l - 1);
                    }
                }
            }

            cout << "\nAdjacency List representation:\n";
            for (int j = 0; j < g.vertices; j++)
            {
                Node *temp = g.adjList[j];
                cout << "Vertex " << char(j + 65) << " is connected to:";
                while (temp != nullptr)
                {
                    cout << " " << char(temp->info + 65);
                    temp = temp->next;
                }
                cout << endl;
            }

            int count = 0;
            int gcount = 0;
            int iscyclic = 0;

            cout << "\nDFS traversal starting from node A:\n";
            g.DFS(0, -1, count, gcount, iscyclic);

            cout << "\nThe graph has " << g.vertices << " vertices.\n";

            if (count == g.vertices)
            {
                cout << "The graph is connected.\n";
            }
            else
            {
                cout << "The graph is not connected.\n";
            }

            if (iscyclic == 1)
            {
                cout << "The graph has a cycle.\n";
            }
            else
            {
                cout << "The graph does not have a cycle.\n";
            }

            if (k == 0)
            {
                fp2 << n << "\t" << gcount << endl;
            }
            else
            {
                fp1 << n << "\t" << gcount << endl;
            }
        }

        fp1.close();
        fp2.close();
    }
};

int main()
{
    Graph g(0); // Initialize with 0 vertices
    for (int i = 0; i < 2; i++)
    {
        g.plotter(i);
    }
    cout << "Data entered into the files.\n";
    return 0;
}