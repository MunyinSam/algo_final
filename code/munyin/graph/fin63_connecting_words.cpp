#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

bool is_connected(const string &w1, const string &w2, int L)
{
    return w1.substr(1) == w2.substr(0, L - 1);
}

int get_index(const vector<string> &words, const string &target)
{
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == target)
        {
            return i;
        }
        }
    return -1;
}

void solve()
{

    int L, N, T;
    cin >> L >> N >> T;

    vector<string> words(N);

    for (int i = 0; i < N; i++)
    {
        cin >> words[i];
    }

    vector<vector<int>> adj(N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (is_connected(words[i], words[j], L))
            {
                adj[i].push_back(j);
            }
        }
    }

    for (int k = 0; k < T; k++)
    {
        string w1, w2;
        cin >> w1 >> w2;

        int start_node = get_index(words, w1);
        int end_node = get_index(words, w2);

        queue<int> q;
        q.push(start_node);

        vector<bool> visited(N, false);
        visited[start_node] = true;

        bool found = false;

        while (!q.empty())
        {
            int u = q.front();

            q.pop();

            if (u == end_node)
            {
                found = true;
                break;
            }

            for (int v : adj[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        if (found)
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}