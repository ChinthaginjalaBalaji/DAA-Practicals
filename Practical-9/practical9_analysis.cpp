#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

class Graph {

    int V;
    vector<vector<pair<int, int>>> adj;

public:

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Prim's Algorithm (Min-Heap); returns total weight of the MST
    long long primMST(int start) {

        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>> pq;

        key[start] = 0;
        pq.push({0, start});
        long long total = 0;

        while (!pq.empty()) {

            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;
            total += key[u];

            for (auto &p : adj[u]) {
                int v = p.first, w = p.second;
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    pq.push({key[v], v});
                }
            }
        }
        return total;
    }
};

// Build a connected random graph with V vertices and E edges (fixed seed)
Graph generateGraph(int V, int E) {

    mt19937 rng(42);
    Graph g(V);

    for (int i = 1; i < V; i++) {                  // spanning chain keeps it connected
        int j = rng() % i;
        g.addEdge(i, j, rng() % 100 + 1);
    }
    for (int i = V - 1; i < E; i++) {              // remaining random edges
        int u = rng() % V, v = rng() % V;
        if (u == v) { i--; continue; }
        g.addEdge(u, v, rng() % 100 + 1);
    }
    return g;
}

int main() {

    int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000};

    cout << "Prim's Algorithm Performance Analysis" << endl << endl;

    for (int V : sizes) {

        int E = 5 * V;
        Graph g = generateGraph(V, E);

        long long weight = 0, us = LLONG_MAX;

        for (int run = 0; run < 3; run++) {          // best of 3 runs
            auto start = high_resolution_clock::now();
            weight = g.primMST(0);
            auto stop = high_resolution_clock::now();
            us = min(us, (long long)duration_cast<microseconds>(stop - start).count());
        }

        cout << "Number of Vertices = " << V << endl;
        cout << "Number of Edges    = " << E << endl;
        cout << "MST Total Weight   : " << weight << endl;
        cout << "Prim's Time        : " << us << " microseconds" << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
