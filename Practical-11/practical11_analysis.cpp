#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

const int INF = 1000000000;

// Floyd-Warshall Algorithm (all pairs shortest paths)
void floydWarshall(vector<vector<int>> &dist, int V) {

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// Build a random directed graph with V vertices and E edges (fixed seed)
vector<vector<int>> generateGraph(int V, int E) {

    mt19937 rng(42);
    vector<vector<int>> dist(V, vector<int>(V, INF));

    for (int i = 0; i < V; i++) dist[i][i] = 0;

    for (int i = 0; i < E; i++) {
        int u = rng() % V, v = rng() % V;
        if (u == v) { i--; continue; }
        dist[u][v] = rng() % 100 + 1;
    }
    return dist;
}

int main() {

    int sizes[] = {10, 50, 100, 200, 300, 400, 500};

    cout << "Floyd-Warshall Algorithm Performance Analysis" << endl << endl;

    for (int V : sizes) {

        int E = 5 * V;
        vector<vector<int>> original = generateGraph(V, E);
        vector<vector<int>> dist;
        long long us = LLONG_MAX;

        for (int run = 0; run < 3; run++) {          // best of 3 runs
            dist = original;                         // fresh copy (not timed)
            auto start = high_resolution_clock::now();
            floydWarshall(dist, V);
            auto stop = high_resolution_clock::now();
            us = min(us, (long long)duration_cast<microseconds>(stop - start).count());
        }

        cout << "Number of Vertices = " << V << endl;
        cout << "Number of Edges    = " << E << endl;
        cout << "Shortest Distance  : ";
        if (dist[0][V - 1] == INF) cout << "No path from 0 to " << V - 1 << endl;
        else cout << dist[0][V - 1] << " (0 to " << V - 1 << ")" << endl;
        cout << "Floyd Time         : " << us << " microseconds" << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
