#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Function to check if 'to' can follow 'from'
// Rule: Suffix of 'from' (L-1) == Prefix of 'to' (L-1)
bool can_follow(const string &from, const string &to, int L)
{
    // from.substr(1) takes characters from index 1 to the end (length L-1)
    // to.substr(0, L-1) takes the first L-1 characters
    return from.substr(1) == to.substr(0, L - 1);
}

// Helper to find the index of a word in the list
int get_index(const vector<string> &words, const string &target)
{
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == target)
            return i;
    }
    return -1; // Should not happen based on problem constraints
}

void solve()
{
    int L, N, T;
    if (!(cin >> L >> N >> T))
        return;

    vector<string> words(N); // Resize vector immediately to hold N words
    for (int i = 0; i < N; i++)
    {
        cin >> words[i];
    }

    // 1. Build the Graph (Adjacency List)
    // adj[i] contains a list of indices that word[i] can connect TO
    vector<vector<int>> adj(N);

    // Check every permutation of words (Directed Graph)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue; // A word usually doesn't flow to itself effectively in this context
            if (can_follow(words[i], words[j], L))
            {
                adj[i].push_back(j);
            }
        }
    }

    // 2. Process Queries
    for (int k = 0; k < T; k++)
    {
        string w1, w2;
        cin >> w1 >> w2;

        int start_node = get_index(words, w1);
        int end_node = get_index(words, w2);

        // Perform BFS to see if end_node is reachable from start_node
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

            // Visit neighbors
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
            cout << "yes" << "\n"; // [cite: 14]
        else
            cout << "no" << "\n"; // [cite: 15]
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}