#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

int solve()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, z, d, e;
    cin >> n >> z >> d >> e;

    vector<int> stations(n);

    for (int i = 0; i < n; i++)
    {
        cin >> stations[i];
    }

    int cur_pos = 0;
    int stops = 0;

    while (cur_pos < z)
    {

        if (cur_pos + d + e >= z)
        {
            return stops;
        }

        int empty_pos = cur_pos + d;
        bool can_remote_refill = false;

        auto it = lower_bound(stations.begin(), stations.end(), empty_pos);

        if (it != stations.end())
        {
            if (*it <= empty_pos + e)
            {
                can_remote_refill = true;
            }
        }

        if (can_remote_refill)
        {
            cur_pos = empty_pos;
            stops++;
            continue;
        }

        auto it_limit = upper_bound(stations.begin(), stations.end(), cur_pos + d);
        
    }
}

int main()
{
    solve();
    return 0;
}