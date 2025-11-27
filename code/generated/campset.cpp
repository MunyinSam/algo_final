
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Structure to represent a candidate route (edge)
struct Route
{
    int u, v; // Camp sites connected
    int cost; // Construction cost (C >= 1) or -1 (forest)
    int type; // 0 for non-forest (cost >= 1), 1 for forest (cost == -1)
};

// Custom comparison function for sorting edges in Kruskal's algorithm
bool compareRoutes(const Route &a, const Route &b)
{
    // Primary Priority: Non-forest (type 0) is better than forest (type 1)
    if (a.type != b.type)
    {
        return a.type < b.type; // Non-forest (0) comes before forest (1)
    }

    // Secondary Priority (only for non-forest routes): Lower cost is better
    if (a.type == 0)
    {
        return a.cost < b.cost;
    }

    // Secondary Priority (for forest routes): Their relative order does not affect the final result.
    return false;
}

// Disjoint Set Union (DSU) / Union-Find Data Structure
// Used to efficiently check connectivity and unite components.
struct DSU
{
    std::vector<int> parent;
    DSU(int n)
    {
        // Size N+1 to handle 1-based indexing for camp sites (1 to N)
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent[i] = i
    }

    // Find the representative (root) of the set containing i
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression for efficiency
    }

    // Union (merge) the sets containing a and b
    bool unite(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);
        if (root_a != root_b)
        {
            parent[root_a] = root_b;
            return true; // Union successful (a new edge was added to the MST)
        }
        return false; // They were already connected (adding this edge would create a cycle)
    }
};

void solve()
{
    // N = number of camp sites, M = number of candidate routes
    int N, M;
    // Fast input reading
    if (!(std::cin >> N >> M))
        return;

    std::vector<Route> routes(M);
    for (int i = 0; i < M; ++i)
    {
        // Read A, B, and C
        std::cin >> routes[i].u >> routes[i].v >> routes[i].cost;

        // Assign type: 0 for non-forest (cost >= 1), 1 for forest (cost == -1)
        routes[i].type = (routes[i].cost == -1) ? 1 : 0;
    }

    // Step 1: Sort the routes based on the custom priority
    std::sort(routes.begin(), routes.end(), compareRoutes);

    // Step 2: Initialize DSU structure
    DSU dsu(N);

    // Variables to track the required output
    long long total_min_cost = 0;
    int forest_routes_count = 0;
    int edges_in_mst = 0;

    // Step 3: Kruskal's Algorithm
    for (const auto &route : routes)
    {
        // Stop when N-1 edges have been selected (a spanning tree is complete)
        if (edges_in_mst == N - 1)
        {
            break;
        }

        // Check if adding this route connects two previously unconnected components
        if (dsu.unite(route.u, route.v))
        {
            // This route is part of the Minimum Spanning Tree
            edges_in_mst++;

            if (route.type == 1)
            {
                // Forest route (cost == -1)
                forest_routes_count++;
            }
            else
            {
                // Non-forest route (cost >= 1)
                total_min_cost += route.cost;
            }
        }
    }

    // Step 4: Output the two required integers
    std::cout << forest_routes_count << " " << total_min_cost << "\n";
}

int main()
{
    // This is required for competitive programming environments for speed.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();
    return 0;
}