#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

// Held-Karp dynamic programming; returns minimum tour cost
int tspDP(const vector<vector<int>> &cost, int n) {

    int FULL = 1 << n;
    vector<vector<int>> dp(FULL, vector<int>(n, INT_MAX));

    dp[1][0] = 0;

    for (int mask = 1; mask < FULL; mask++) {

        if (!(mask & 1)) continue;

        for (int i = 0; i < n; i++) {

            if (!(mask & (1 << i)) || dp[mask][i] == INT_MAX) continue;

            for (int j = 0; j < n; j++) {

                if (mask & (1 << j)) continue;

                int newMask = mask | (1 << j);
                dp[newMask][j] = min(dp[newMask][j], dp[mask][i] + cost[i][j]);
            }
        }
    }

    int best = INT_MAX;
    for (int i = 1; i < n; i++)
        best = min(best, dp[FULL - 1][i] + cost[i][0]);

    return best;
}

// Brute force: try every permutation of cities 1 .. n-1
int tspBruteForce(const vector<vector<int>> &cost, int n) {

    vector<int> perm;
    for (int i = 1; i < n; i++) perm.push_back(i);

    int best = INT_MAX;

    do {
        int total = cost[0][perm[0]];
        for (int i = 0; i + 1 < n - 1; i++)
            total += cost[perm[i]][perm[i + 1]];
        total += cost[perm[n - 2]][0];
        best = min(best, total);
    } while (next_permutation(perm.begin(), perm.end()));

    return best;
}

// Build a random symmetric cost matrix (fixed seed)
vector<vector<int>> generateCost(int n) {

    mt19937 rng(42);
    vector<vector<int>> cost(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            cost[i][j] = cost[j][i] = rng() % 100 + 1;

    return cost;
}

int main() {

    int sizes[] = {5, 8, 10, 11, 12, 14, 15};

    cout << "TSP Algorithm Performance Analysis" << endl << endl;

    for (int n : sizes) {

        vector<vector<int>> cost = generateCost(n);

        int dpCost = 0;
        long long dpTime = LLONG_MAX;

        for (int run = 0; run < 3; run++) {          // best of 3 runs
            auto s1 = high_resolution_clock::now();
            dpCost = tspDP(cost, n);
            auto e1 = high_resolution_clock::now();
            dpTime = min(dpTime, (long long)duration_cast<microseconds>(e1 - s1).count());
        }

        cout << "Number of Cities   = " << n << endl;
        cout << "Held-Karp Cost     : " << dpCost << endl;
        cout << "Held-Karp Time     : " << dpTime << " microseconds" << endl;

        if (n <= 11) {                       // brute force is too slow beyond this
            int bfCost = 0;
            long long bfTime = LLONG_MAX;

            for (int run = 0; run < 3; run++) {      // best of 3 runs
                auto s2 = high_resolution_clock::now();
                bfCost = tspBruteForce(cost, n);
                auto e2 = high_resolution_clock::now();
                bfTime = min(bfTime, (long long)duration_cast<microseconds>(e2 - s2).count());
            }

            cout << "Brute Force Cost   : " << bfCost << endl;
            cout << "Brute Force Time   : " << bfTime << " microseconds" << endl;
        } else {
            cout << "Brute Force Cost   : Skipped (too slow)" << endl;
            cout << "Brute Force Time   : Skipped (too slow)" << endl;
        }
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
