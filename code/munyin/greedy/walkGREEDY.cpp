#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve()
{
    int N, Z, D, E;
    // Input validation
    if (!(cin >> N >> Z >> D >> E))
        return 0;

    vector<int> stations(N);
    for (int i = 0; i < N; i++)
    {
        cin >> stations[i];
    }

    int current_pos = 0;
    int stops = 0;

    // While we haven't reached the destination
    while (current_pos < Z)
    {

        // 1. WIN CHECK: Can we reach Z directly?
        // We can drive D and walk E. Max reach = D + E.
        if (current_pos + D + E >= Z)
        {
            return stops;
        }

        // 2. TRY REMOTE REFILL (Greedy Choice)
        // We drive until empty at (current_pos + D).
        // Then we look for a station AHEAD of us within walking distance E.
        // We only look ahead because the rules say "never walk back to stations passed".

        int empty_pos = current_pos + D;
        bool can_remote_refill = false;

        // Use binary search (lower_bound) to find the first station >= empty_pos
        auto it = lower_bound(stations.begin(), stations.end(), empty_pos);

        // Check if this station is within walking range (empty_pos + E)
        if (it != stations.end())
        {
            if (*it <= empty_pos + E)
            {
                can_remote_refill = true;
            }
        }

        if (can_remote_refill)
        {
            // We successfully refilled remotely!
            // Our car is now full at the empty_pos.
            current_pos = empty_pos;
            stops++;
            continue; // Start next cycle from new position
        }

        // 3. FALLBACK: DIRECT DRIVE
        // If we can't remote refill, we MUST stop at a station we can drive to.
        // We want the furthest station possible to maximize progress.
        // Search for the furthest station <= current_pos + D

        auto it_limit = upper_bound(stations.begin(), stations.end(), current_pos + D);

        // If no stations are reachable ahead of us
        if (it_limit == stations.begin())
        {
            return -1;
        }

        // Move iterator back to get the largest station <= limit
        int next_station = *(--it_limit);

        // Verify we are actually moving forward (not stuck)
        if (next_station <= current_pos)
        {
            return -1;
        }

        // Move to that station
        current_pos = next_station;
        stops++;
    }

    return stops;
}

int main()
{
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << solve() << endl;
    return 0;
}