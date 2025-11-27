#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

void solve()
{
    int N, L;

    cin >> N >> L;

    vector<int> prices(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> prices[i];
    }

    sort(prices.begin(), prices.end());

    int left = 0;
    int max_items = 0;

    for (int right = 0; right < N; ++right)
    {
        while (prices[right] - prices[left] > L)
        {
            left++;
        }

        int current_length = right - left + 1;
        max_items = max(max_items, current_length);
    }
    cout << max_items << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}