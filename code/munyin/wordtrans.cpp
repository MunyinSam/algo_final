#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

bool is_transformable(const string &w1, const string &w2)
{
    if (w1.length() != w2.length())
    {
        return false;
    }

    int diff_count = 0;
    for (size_t i = 0; i < w1.length(); ++i)
    {
        if (w1[i] != w2[i])
        {
            diff_count++;
        }
    }

    return diff_count == 1;
}

void solve_test_case()
{
    vector<string> dictionary;
    string word;

    while (cin >> word && word != "*")
    {
        dictionary.push_back(word);
    }

    map<string, vector<string>> graph;

    for (const string &w : dictionary)
    {
        graph[w] = vector<string>();
    }

    for (size_t i = 0; i < dictionary.size(); i++)
    {
        for (size_t j = i + 1; j < dictionary.size(); j++)
        {
            if (is_transformable(dictionary[i], dictionary[j]))
            {
                graph[dictionary[i]].push_back(dictionary[j]);
                graph[dictionary[j]].push_back(dictionary[i]);
            }
        }
    }

    string line;
    // Consume the remaining newline character after the dictionary loop
    if (cin.peek() == '\n')
        cin.ignore();

    while (getline(cin, line) && !line.empty())
    {
        stringstream ss(line);
        string start_word, end_word;
        ss >> start_word >> end_word;

        if (start_word.empty() || end_word.empty())
            continue;

        if (start_word == end_word)
        {
            cout << start_word << " " << end_word << " 0" << endl;
            continue;
        }

        // --- 3. Run BFS for Shortest Path ---
        // distance maps word to minimum steps from start_word
        map<string, int> distance;
        queue<string> q;

        distance[start_word] = 0;
        q.push(start_word);
        int steps = -1;

        while (!q.empty())
        {
            string current_word = q.front();
            q.pop();

            if (current_word == end_word)
            {
                steps = distance[current_word];
                break;
            }

            for (const string &neighbor : graph[current_word])
            {
                if (distance.find(neighbor) == distance.end())
                {
                    distance[neighbor] = distance[current_word] + 1;
                    q.push(neighbor);
                }
            }
        }

        cout << start_word << " " << end_word << " " << steps << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N))
        return 0;

    string dummy_line;
    getline(cin, dummy_line);
    getline(cin, dummy_line);

    for (int i = 0; i < N; ++i)
    {
        if (i > 0)
        {
            cout << endl;
        }
        solve_test_case();
    }
    return 0;
}