#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Define the structure for an edge
struct Edge
{
    int u, v; // Vertices
    int weight;
};

// Custom comparator for sorting edges by weight
bool compareEdges(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

// --- Disjoint Set Union (DSU) Structure ---

class DSU
{
private:
    std::vector<int> parent;
    std::vector<int> rank; // Used for optimization (union by rank)
public:
    DSU(int n)
    {
        // Initialize parent[i] = i and rank[i] = 0 for all vertices
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0); // Fill with 0, 1, 2, ... n
        rank.assign(n + 1, 0);
    }

    // Find operation with Path Compression optimization
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        // Path Compression: makes the root the direct parent of i
        return parent[i] = find(parent[i]);
    }

    // Union operation with Union by Rank optimization
    void unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j)
        {
            // Attach smaller rank tree under the root of high rank tree
            if (rank[root_i] < rank[root_j])
            {
                parent[root_i] = root_j;
            }
            else if (rank[root_i] > rank[root_j])
            {
                parent[root_j] = root_i;
            }
            else
            {
                // If ranks are the same, make one as root and increment its rank
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

// --- Kruskal's Algorithm Implementation ---

long long kruskalMST(int N, std::vector<Edge> &edges)
{
    // 1. Sort all edges by weight
    std::sort(edges.begin(), edges.end(), compareEdges);

    // 2. Initialize DSU structure
    DSU dsu(N);

    long long mst_weight = 0;
    int edges_count = 0;

    // 3. Iterate through sorted edges and build the MST
    for (const auto &edge : edges)
    {
        // Check if including this edge creates a cycle (i.e., if u and v are already in the same set)
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            // If they are in different sets, include the edge
            mst_weight += edge.weight;
            dsu.unite(edge.u, edge.v);
            edges_count++;
        }

        // Optimization: MST is formed when N-1 edges are included
        if (edges_count == N - 1)
        {
            break;
        }
    }

    // Note: The problem constraints suggest the graph is connected,
    // so we don't strictly need to check for edges_count < N - 1 for a valid MST.
    // If the graph is guaranteed to be connected, edges_count will be N-1.
    return mst_weight;
}

// --- Main Function ---

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M;
    // Read N (vertices) and M (edges)
    if (!(std::cin >> N >> M))
        return 0;

    std::vector<Edge> edges;
    edges.reserve(M);

    // Read M edges
    for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        if (!(std::cin >> u >> v >> w))
            break;
        edges.push_back({u, v, w});
    }

    // Calculate and output the weight of the Minimum Spanning Tree
    long long result = kruskalMST(N, edges);
    std::cout << result << "\n";

    return 0;
}