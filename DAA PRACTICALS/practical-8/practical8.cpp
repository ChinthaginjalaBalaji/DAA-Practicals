#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {

    int V;
    vector<vector<int>> adj;

public:

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add an undirected edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Display adjacency list
    void displayGraph() {

        cout << "\n--- Adjacency List ---" << endl;

        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int v : adj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    // 1. Breadth First Search (uses Queue)
    void BFS(int start) {

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\n--- BFS Traversal ---" << endl;

        while (!q.empty()) {

            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    // 2. Depth First Search (recursive helper)
    void DFSUtil(int u, vector<bool> &visited) {

        visited[u] = true;
        cout << u << " ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                DFSUtil(v, visited);
            }
        }
    }

    void DFS(int start) {

        vector<bool> visited(V, false);

        cout << "\n--- DFS Traversal ---" << endl;
        DFSUtil(start, visited);
        cout << endl;
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter edges (u v):" << endl;

    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid edge. Vertices must be between 0 and "
                 << V - 1 << "." << endl;
            i--;
            continue;
        }

        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    if (start < 0 || start >= V) {
        cout << "Invalid starting vertex." << endl;
        return 0;
    }

    g.displayGraph();
    g.BFS(start);
    g.DFS(start);

    return 0;
}
