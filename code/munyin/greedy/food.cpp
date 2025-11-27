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

    int N;
    cin >> N;

    vector<int> A(N);
    map<int, int> count;

    for (int i = 0; i < N; i++)
    {
        int value;
        cin >> value;
        A[i] = value;
        count[value]++;
    }

    vector<int> favfood;
    int maxCount = 0;

    for (const auto &pair : count)
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            favfood = {pair.first};
        }
        else if (pair.second == maxCount)
        {
            favfood.push_back(pair.first);
        }
    }

    sort(favfood.begin(), favfood.end());

    for (int i = 0; i < favfood.size(); ++i)
    {
        cout << favfood[i] << (i == favfood.size() - 1 ? "" : " ");
    }
}

int main()
{
    solve();
    return 0;
}