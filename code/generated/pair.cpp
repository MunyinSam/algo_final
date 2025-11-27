#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void solve_optimal()
{
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, g, t;
    if (!(cin >> n >> g >> t))
        return;

    // Use long long for intermediate sums and bounds to prevent overflow,
    // especially since G and T are likely large integers.
    long long low_bound = (long long)g - t;
    long long up_bound = (long long)g + t;

    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    // --- 1. Sort the array (O(N log N)) ---
    // Sorting is the crucial step that enables fast searching.
    sort(x.begin(), x.end());

    long long pair_amount = 0;

    // --- 2. Iterate and Search (O(N log N)) ---
    for (int i = 0; i < n; i++)
    {
        long long current_val = x[i];

        // Define the target range for the partner x[j]
        long long target_low = low_bound - current_val;
        long long target_high = up_bound - current_val;

        // Use the subarray starting from i + 1 to avoid double-counting and self-pairing
        auto start_it = x.begin() + i + 1;
        auto end_it = x.end();

        // Find the first element >= target_low
        auto it_low = lower_bound(start_it, end_it, target_low);

        // Find the first element > target_high
        // Note: upper_bound finds the first element *greater* than the target
        auto it_high = upper_bound(start_it, end_it, target_high);

        // The count of valid partners is the distance between the two iterators
        pair_amount += distance(it_low, it_high);
    }

    cout << pair_amount << endl;
}

int main()
{
    solve_optimal();
    return 0;
}