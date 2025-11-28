#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

// Define a struct to hold the demand interval [a, b]
// Using a struct makes the code clearer than nested pairs.
struct Demand
{
    long long a; // Start gem index (inclusive)
    long long b; // End gem index (inclusive)
};

// Custom comparison function for sorting.
// We sort primarily by the end position (b) in ascending order.
bool compareDemands(const Demand &d1, const Demand &d2)
{
    // If the end positions are the same, it doesn't matter much which order they go.
    // However, for consistency, we can sort by start position (a) if ends are equal.
    if (d1.b != d2.b)
    {
        return d1.b < d2.b; // Sort by earliest end time (b)
    }
    return d1.a < d2.a; // Tie-breaker: sort by earliest start time (a)
}

void solve()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N; // Total number of gems (up to 10^9) - we only need it for context.
    int M;       // Total number of demands (up to 100,000)

    // Read N and M
    if (!(cin >> N >> M))
        return;

    vector<Demand> demands(M);

    // Read all M demands [a_i, b_i]
    for (int i = 0; i < M; ++i)
    {
        // Since a and b are up to 10^9, they must be long long.
        if (!(cin >> demands[i].a >> demands[i].b))
            return;
    }

    // 1. Sort the demands using the custom comparator
    // The complexity of this step is O(M log M).
    sort(demands.begin(), demands.end(), compareDemands);

    // 2. Apply the Greedy Algorithm

    int satisfied_demands_count = 0;

    // Tracks the end position of the last selected demand.
    // Initialize to a value that ensures the first demand is always selected.
    // 0 is safe since gem indices start at 1.
    long long last_end_position = 0;

    for (const auto &demand : demands)
    {
        // Check for non-overlap condition:
        // The new demand's start position (a) must be greater than the end position
        // of the last selected demand (b) to ensure it doesn't overlap.
        // E.g., if last demand was [2, 5], last_end_position is 5.
        // A new demand [6, 8] works (6 > 5).
        // A demand [5, 7] does not work (5 is not > 5) as the 5th gem is shared.
        if (demand.a > last_end_position)
        {
            // Select this demand
            satisfied_demands_count++;

            // Update the end position of the last selected demand
            last_end_position = demand.b;
        }
    }

    // Output the maximum number of satisfied demands
    cout << satisfied_demands_count << "\n";
}

int main()
{
    // The problem statement implies multiple test cases may follow,
    // but the input example only shows one N M line pair.
    // We stick to the single execution based on the structure, but a production
    // version might include a loop if multiple test cases are expected.
    solve();

    return 0;
}