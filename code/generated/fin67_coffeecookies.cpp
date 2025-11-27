#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits> // Included for INF definition

using namespace std;

// Define a type for long long distances to prevent overflow
typedef long long ll;
// Pair to store edge information: {destination, weight}
typedef pair<int, int> Edge;
// Pair for the priority queue: {distance, node}
typedef pair<ll, int> State;

// Define INF (a large value to represent unreachable, safe from overflow when added)
const ll INF = numeric_limits<ll>::max() / 2;


// --- 1. Dijkstra's Algorithm Implementation (MOVED OUTSIDE solve) ---

// Global variable N is needed for array sizing. A better way would be to pass it as an argument.
// For simplicity in this fix, we'll assume N is passed in the parameter list.

/**
 * @brief Finds the shortest path from a set of starting nodes (Multi-Source Dijkstra).
 * @param N Total number of nodes.
 * @param graph The adjacency list.
 * @param start_nodes A list of {node, initial_distance} pairs.
 * @return vector<ll> The shortest distance from the nearest start node to every node j.
 */
vector<ll> dijkstra(int N, const vector<vector<Edge>>& graph, const vector<pair<int, ll>>& start_nodes) {
    // Initialize distances using INF, replacing the original -1 sentinel for robustness.
    vector<ll> dist(N + 1, INF); 
    // Priority Queue: stores {current_distance, node} (Min-Heap)
    priority_queue<State, vector<State>, greater<State>> pq;

    // Initialize starting nodes
    for (const auto& start : start_nodes) {
        int u = start.first;
        ll d = start.second;
        if (d < dist[u]) {
            dist[u] = d;
            pq.push({d, u});
        }
    }

    while (!pq.empty()) {
        ll d_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Optimization: Skip stale entries
        if (d_u > dist[u]) {
            continue;
        }

        // Explore neighbors
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            ll new_dist = d_u + weight;

            // Relaxation step: If a shorter path is found
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                pq.push({new_dist, v});
            }
        }
    }
    return dist;
}

// --- 2. Graph and Input Processing (solve function) ---

void solve() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return;

    // Adjacency List: adj[u] = list of {v, w} where v is neighbor and w is weight
    vector<vector<Edge>> adj(N + 1); 
    // X[j] stores the shop type at intersection j
    vector<int> X(N + 1); 

    // Read shop types
    for (int j = 1; j <= N; ++j) {
        cin >> X[j];
    }

    // Read M streets and build the graph (two-way connections)
    for (int i = 0; i < M; ++i) {
        int U, V, W;
        cin >> U >> V >> W;
        adj[U].push_back({V, W});
        adj[V].push_back({U, W});
    }

    // --- 3. Solve based on K ---

    // The logic below relies on the INF constant instead of -1.
    ll min_time = INF;

    // Define a lambda function to wrap the call and pass N
    auto run_dijkstra = [&](const vector<pair<int, ll>>& starts) {
        return dijkstra(N, adj, starts);
    };

    if (K == 1) {
        // Case K=1: House (1) -> Any Coffee Shop (Xj=1)
        vector<ll> dist_from_house = run_dijkstra({{1, 0}});

        for (int j = 1; j <= N; ++j) {
            // Is it a Coffee Shop AND is it reachable?
            if (X[j] == 1 && dist_from_house[j] != INF) {
                min_time = min(min_time, dist_from_house[j]);
            }
        }

    } else if (K == 2) {
        // Case K=2: House (1) -> Coffee Shop (C) -> Cookie Shop (D)

        // Step 1: Calculate shortest path from House (1) to all nodes
        vector<ll> dist_from_house = run_dijkstra({{1, 0}});

        // Step 2: Calculate shortest path from ALL Cookie Shops (Multi-Source Dijkstra)
        vector<pair<int, ll>> cookie_starts;
        for (int j = 1; j <= N; ++j) {
            if (X[j] == 2) { 
                cookie_starts.push_back({j, 0});
            }
        }
        
        vector<ll> dist_to_cookie = run_dijkstra(cookie_starts); 

        // Step 3: Iterate through all Coffee Shops (C) to find the minimum total time
        for (int C = 1; C <= N; ++C) {
            if (X[C] == 1) {
                ll time_1_to_C = dist_from_house[C];
                ll time_C_to_D = dist_to_cookie[C]; 

                // Check if both segments are reachable (not INF)
                if (time_1_to_C != INF && time_C_to_D != INF) {
                    ll total_time = time_1_to_C + time_C_to_D;
                    min_time = min(min_time, total_time);
                }
            }
        }
    }

    // --- 4. Output ---
    
    // If min_time is still INF, it means no path was found (though the problem guarantees one).
    // The original code used -1, so let's check for that condition if we were to strictly follow the original logic's output requirement.
    if (min_time == INF) {
        // This case should not happen based on problem constraints, but as a safe guard:
        cout << -1 << endl; 
    } else {
        cout << min_time << endl;
    }
}

// Boilerplate main function
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}