#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

using namespace std;

// 1. Type Definitions for Clarity and Safety
typedef long long ll;
// Edge: {destination_node, weight}
typedef pair<int, int> Edge;
// State: {distance, current_node} -- IMPORTANT: distance comes first for priority queue sorting
typedef pair<ll, int> State;

// A constant for "infinity" to represent unreachable nodes or uninitialized distances
// We use a large number instead of numeric_limits<ll>::max() to prevent overflow during addition
const ll INF = numeric_limits<ll>::max() / 2;

/**
 * @brief Finds the shortest path from a source (or multiple sources) to all other nodes.
 * @param N Total number of nodes (1-indexed).
 * @param adj The adjacency list: adj[u] = list of {v, weight}.
 * @param start_nodes A vector of {node, initial_distance} pairs.
 * @return vector<ll> The shortest distance from the nearest start node to every node j.
 */
vector<ll> dijkstra(int N, const vector<vector<Edge>> &adj, const vector<pair<int, ll>> &start_nodes)
{
    // 2. Initialization
    // dist[j] will store the minimum time/weight from the source to node j.
    vector<ll> dist(N + 1, INF);
    // Min-Heap Priority Queue: Stores {distance, node}, prioritized by smallest distance.
    priority_queue<State, vector<State>, greater<State>> pq;

    // Handle Multi-Source Initialization
    for (const auto &start : start_nodes)
    {
        int u = start.first;
        ll d = start.second;
        if (d < dist[u])
        { // In case the same node is listed multiple times
            dist[u] = d;
            pq.push({d, u});
        }
    }

    // 3. Main Algorithm Loop
    while (!pq.empty())
    {
        // Pop the state with the smallest known distance (u)
        ll d_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Optimization: If we found a shorter path to u already, ignore this older, longer entry.
        if (d_u > dist[u])
        {
            continue;
        }

        // 4. Relaxation Step: Explore neighbors (v) of u
        for (const auto &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;
            ll new_dist = d_u + weight;

            // Relaxation: If the path through u is shorter than the current shortest path to v
            if (new_dist < dist[v])
            {
                dist[v] = new_dist;
                pq.push({new_dist, v}); // Add the new, shorter path to the priority queue
            }
        }
    }

    return dist; // Contains the shortest distances from the source(s)
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;

    cin >> N >> M;

    vector<vector<Edge>> adj(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        // For undirected graphs (like your problem):
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        // For directed graphs, only include the forward edge:
        // adj[u].push_back({v, w});
    }

    vector<ll> dist = dijkstra(N, adj, {{1, 0}});
    if (dist[N] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[N] << endl;
    }

    return 0;
}