#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // Include cmath for max function, though std::max works fine

using namespace std;

void solve_case(int n, int d, int r)
{
    // The total overtime payment should be a long long to be safe,
    // as it can accumulate large values (up to 10 million in this case).
    long long total_overtime = 0;

    vector<int> morning(n);
    vector<int> evening(n);

    // Read morning route lengths
    for (int i = 0; i < n; ++i)
    {
        cin >> morning[i];
    }

    // Read evening route lengths
    for (int i = 0; i < n; ++i)
    {
        cin >> evening[i];
    }

    // 1. Sort the morning routes in ASCENDING order (smallest first)
    sort(morning.begin(), morning.end());

    // 2. Sort the evening routes in DESCENDING order (largest first)
    // We use std::sort with std::rbegin() and std::rend() for reverse sorting.
    sort(evening.rbegin(), evening.rend());

    // 3. Pair the routes and calculate payment
    for (int i = 0; i < n; i++)
    {
        // Pair: morning[i] (smallest) + evening[i] (largest)
        long long total_length = (long long)morning[i] + evening[i];

        if (total_length > d)
        {
            // Overtime is (total length - limit d) * rate r
            long long overtime_amount = (total_length - d) * r;
            total_overtime += overtime_amount;
        }
    }

    cout << total_overtime << endl;
}

void solve()
{
    // Optimization flags
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d, r;

    // Input loop to handle multiple test cases
    while (cin >> n >> d >> r)
    {
        // Stop condition: case with three zeros
        if (n == 0 && d == 0 && r == 0)
        {
            break;
        }

        solve_case(n, d, r);
    };
}

int main()
{
    solve();
    return 0;
}