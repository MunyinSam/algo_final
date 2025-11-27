#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

bool check(int lower_bound, int upper_bound, int amount)
{
    return (amount >= lower_bound && amount <= upper_bound);
}

void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, g, t;
    cin >> n >> g >> t;

    long long lower_bound = (long long)g - t;
    long long upper_bound = (long long)g + t;

    vector<int> x(n);

    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    long long pair_amount = 0;

    for (int i = 0; i < n; i++)
    {
        long long current_val = x[i];

        long long target_low = lower_bound - current_val;
        long long target_high = upper_bound - current_val;

        auto start_it = x.begin() + i + 1;
        auto end_it = x.end();

        auto it_low = lower_bound(start_it, end_it, target_low)
    }

    cout << pair_amount << endl;
}

int main()
{
    solve();
    return 0;
}