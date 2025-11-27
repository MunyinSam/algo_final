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

    int n, m, l, s, t;
    cin >> n >> m >> l >> s >> t;

    s -= 1;
    t -= 1;

    vector<int> room_heights(n);

    for (int i = 0; i < n; i++)
    {
        cin >> room_heights[i];
    }

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        int u = a - 1; // 0-based index for room A
        int v = b - 1;

        long long h_u = room_heights[u];
        long long h_v = room_heights[v];

        if (h_v <= h_u + l)
        {
            adj[u].push_back(v);
        }

        if (h_u <= h_v + l)
        {
            adj[v].push_back(u);
        }
    }


    queue<int> q;
    vector<int> dist(n, -1);

    q.push(s);
    dist[s] = 0;

    while (!q.empty())
    {
        int u = q.front();

        q.pop();

        if (u == t)
        {
            break;
        }

        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << dist[t] << endl;
}

int main()
{
    solve();
    return 0;
}