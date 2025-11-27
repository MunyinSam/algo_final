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

void solve()
{
    int N, M, K;

    if (!(cin >> N >> M >> K))
        return;

    vector<vector<Edge>> adj(N + 1);
    vector<int> X(N + 1);

    for (int j = 1; j <= N; j++)
    {
        cin >> X[j];
    }

    for (int i = 0; i < M; i++)
    {
        int U, V, W;
        cin >> U >> V >> W;
        adj[U].push_back({V, W});
        adj[V].push_back({U, W});
    }

    ll min_time = INF;

    auto run_dijkstra = [&](const vector<pair<int, ll>> &starts)
    {
        return dijkstra(N, adj, starts);
    };

    if (K == 1)
    {
        vector<ll> dist_from_house = run_dijkstra({{1, 0}});

        for (int j = 1; j <= N; j++)
        {
            if (X[j] == 1 && dist_from_house[j] != INF)
            {
                min_time = min(min_time, dist_from_house[j]);
            }
        }
    }
    else if (K == 2)
    {
        vector<ll> dist_from_house = run_dijkstra({{1, 0}});
        vector<pair<int, ll>> cookie_starts;
        for (int j = 1; j <= N; ++j)
        {
            if (X[j] == 2)
            {
                cookie_starts.push_back({j, 0});
            }
        }

        vector<ll> dist_to_cookie = run_dijkstra(cookie_starts);

        for (int C = 1; C <= N; C++)
        {
            if (X[C] == 1)
            {
                ll time_1_to_C = dist_from_house[C];
                ll time_C_to_D = dist_to_cookie[C];

                if (time_1_to_C != INF && time_C_to_D != INF)
                {
                    ll total_time = time_1_to_C + time_C_to_D;
                    min_time = min(min_time, total_time);
                }
            }
        }
    }

    if (min_time == INF)
    {
        // This case should not happen based on problem constraints, but as a safe guard:
        cout << -1 << endl;
    }
    else
    {
        cout << min_time << endl;
    }
}

// --- Example Usage ---

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
