#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve()
{
    int N, Z, D, E;
    if (!(cin >> N >> Z >> D >> E))
        return 0;

    vector<int> stations(N);
    for (int i = 0; i < N; i++)
    {
        cin >> stations[i];
    }

    // dp[k] stores the max position reachable with k stops
    // In worst case, we stop N times.
    vector<int> dp(N + 1, -1);

    dp[0] = 0; // Base case: 0 stops, pos 0

    for (int k = 0; k <= N; k++)
    {
        int current_pos = dp[k];

        // 1. Check Win Condition
        // From current_pos, we drive D and walk E. If that hits Z, we are done.
        // We return 'k' because we don't need another stop to just arrive at Z.
        if (current_pos + D + E >= Z)
        {
            return k;
        }

        // If we've maxed out stops, break
        if (k == N)
            break;

        // 2. Calculate reach for dp[k+1]
        int best_next_pos = -1;

        // Option A: Remote Refill (Jump to current + D)
        // Check if a station exists in [current_pos + D, current_pos + D + E]
        int limit_walk = current_pos + D + E;
        int limit_drive = current_pos + D;

        // Find first station >= limit_drive
        auto it = lower_bound(stations.begin(), stations.end(), limit_drive);

        if (it != stations.end() && *it <= limit_walk)
        {
            // Success: We can "teleport" to limit_drive
            best_next_pos = limit_drive;
        }
        else
        {
            // Option B: Drive to furthest station
            // Find furthest station <= limit_drive
            auto it2 = upper_bound(stations.begin(), stations.end(), limit_drive);
            if (it2 != stations.begin())
            {
                best_next_pos = *(--it2);

                // Safety check: ensure we are moving forward
                if (best_next_pos <= current_pos)
                    best_next_pos = -1;
            }
        }

        // If we can't move anywhere, stop logic for this path
        if (best_next_pos == -1)
        {
            break;
        }

        dp[k + 1] = best_next_pos;
    }

    return -1; // Impossible
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << solve() << endl;
    return 0;
}