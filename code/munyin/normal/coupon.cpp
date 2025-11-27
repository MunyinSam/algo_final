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
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, W;

    cin >> N >> W;

    vector<int> coupon_value(N);
    map<int, int> coupon_given;

    for (int i = 0; i < N; ++i)
    {
        cin >> coupon_value[i];
        coupon_given[i] = 0;
    }

    int idx = N - 1;

    while (W != 0)
    {
        if (coupon_value[idx] > W)
        {
            idx--;
        }
        else
        {
            W = W - coupon_value[idx];
            coupon_given[coupon_value[idx]]++;
        }
    }

    vector<int> output;

    for (const auto &pair : coupon_given)
    {
        output.push_back(pair.second);
        // cout << pair.second << " ";
    }

    vector<int> res;

    for (int i = N; i > 0; i--)
    {
        res.push_back(output[i]);
    }

    reverse(res.begin(), res.end());

    for (int r : res)
    {
        cout << r << " ";
    }
}

int main()
{
    solve();
    return 0;
}