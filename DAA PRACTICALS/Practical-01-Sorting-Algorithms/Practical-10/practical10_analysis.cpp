#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

struct Edge {
    int u, v, w;
};

class DSU {

    vector<int> parent, rnk;

public:

    DSU(int n) {
        parent.resize(n);
        rnk.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {

        int a = find(x), b = find(y);
        if (a == b) return false;

        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
        return true;
    }
};

// Kruskal's Algorithm; returns total weight of the MST
long long kruskalMST(int V, vector<Edge> edges) {

    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) { return a.w < b.w; });

    DSU dsu(V);
    long long total = 0;
    int count = 0;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            if (++count == V - 1) break;
        }
    }
    return total;
}

// Build a connected random edge list with V vertices and E edges (fixed seed)
vector<Edge> generateEdges(int V, int E) {

    mt19937 rng(42);
    vector<Edge> edges;

    for (int i = 1; i < V; i++) {                  // spanning chain keeps it connected
        int j = rng() % i;
        edges.push_back({i, j, (int)(rng() % 100 + 1)});
    }
    for (int i = V - 1; i < E; i++) {              // remaining random edges
        int u = rng() % V, v = rng() % V;
        if (u == v) { i--; continue; }
        edges.push_back({u, v, (int)(rng() % 100 + 1)});
    }
    return edges;
}

int main() {

    int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000};

    cout << "Kruskal's Algorithm Performance Analysis" << endl << endl;

    for (int V : sizes) {

        int E = 5 * V;
        vector<Edge> edges = generateEdges(V, E);

        long long weight = 0, us = LLONG_MAX;

        for (int run = 0; run < 3; run++) {          // best of 3 runs
            auto start = high_resolution_clock::now();
            weight = kruskalMST(V, edges);
            auto stop = high_resolution_clock::now();
            us = min(us, (long long)duration_cast<microseconds>(stop - start).count());
        }

        cout << "Number of Vertices = " << V << endl;
        cout << "Number of Edges    = " << E << endl;
        cout << "MST Total Weight   : " << weight << endl;
        cout << "Kruskal's Time     : " << us << " microseconds" << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
