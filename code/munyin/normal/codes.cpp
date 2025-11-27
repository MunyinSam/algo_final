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

    vector<int> arr(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    map<int, int> count;

    for (int i = 1; i < N; ++i)
    {
        int diff = abs(arr[i] - arr[i - 1]);
        count[diff]++;
    }

    for (int i = 2; i < N; ++i)
    {
        int diff = abs(arr[i] - arr[i - 2]);
        count[diff]++;
    }

    int mostDuplicatedValue = -1;
    int maxCount = 0;

    for (const auto &pair : count)
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            mostDuplicatedValue = pair.first;
        }
    }
    cout << mostDuplicatedValue << endl;
}

int main()
{
    solve();
    return 0;
}