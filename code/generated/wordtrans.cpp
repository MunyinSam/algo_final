#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

// Function to check if word1 can be transformed into word2 in one step.
// They must have the same length and differ by exactly one character.
bool is_transformable(const string& w1, const string& w2) {
    // Must have the same length 
    if (w1.length() != w2.length()) {
        return false;
    }

    int diff_count = 0;
    for (size_t i = 0; i < w1.length(); ++i) {
        if (w1[i] != w2[i]) {
            diff_count++;
        }
    }
    // Must differ by only a single character position 
    return diff_count == 1;
}

// Function to solve the problem for one test case using BFS
void solve_test_case() {
    vector<string> dictionary;
    string word;
    
    // Read the dictionary until an asterisk (*) is encountered [cite: 10]
    while (cin >> word && word != "*") {
        dictionary.push_back(word);
    }

    // --- 1. Build the Graph (Adjacency List) ---
    // The graph stores connections between transformable words
    map<string, vector<string>> graph;
    
    // Add all words to the graph structure first
    for (const string& w : dictionary) {
        graph[w] = vector<string>();
    }

    // Connect all transformable pairs
    for (size_t i = 0; i < dictionary.size(); ++i) {
        for (size_t j = i + 1; j < dictionary.size(); ++j) {
            if (is_transformable(dictionary[i], dictionary[j])) {
                // Add an edge in both directions (unweighted graph)
                graph[dictionary[i]].push_back(dictionary[j]);
                graph[dictionary[j]].push_back(dictionary[i]);
            }
        }
    }

    // --- 2. Process Transformation Pairs ---
    string line;
    // Consume the remaining newline character after the dictionary loop
    if (cin.peek() == '\n') cin.ignore();
    
    // Read pairs of words, one pair per line [cite: 14]
    while (getline(cin, line) && !line.empty()) {
        stringstream ss(line);
        string start_word, end_word;
        ss >> start_word >> end_word;
        
        if (start_word.empty() || end_word.empty()) continue;

        // If the start and end words are the same, the steps are 0
        if (start_word == end_word) {
            cout << start_word << " " << end_word << " 0" << endl;
            continue;
        }

        // --- 3. Run BFS for Shortest Path ---
        // distance maps word to minimum steps from start_word
        map<string, int> distance;
        queue<string> q;

        // Initialize BFS from the start word
        distance[start_word] = 0;
        q.push(start_word);
        int steps = -1; // Final result steps

        while (!q.empty()) {
            string current_word = q.front();
            q.pop();

            if (current_word == end_word) {
                steps = distance[current_word];
                break;
            }

            // Explore neighbors
            for (const string& neighbor : graph[current_word]) {
                // Check if the neighbor has been visited
                if (distance.find(neighbor) == distance.end()) {
                    distance[neighbor] = distance[current_word] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Output: starting word, ending word, and the number of steps [cite: 20]
        cout << start_word << " " << end_word << " " << steps << endl;
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    // The first line of the input is an integer N (number of test sets) [cite: 9]
    if (!(cin >> N)) return 0;

    // Consume the blank line following N [cite: 9]
    string dummy_line;
    getline(cin, dummy_line); 
    getline(cin, dummy_line);

    for (int i = 0; i < N; ++i) {
        // Separate consecutive output sets by a blank line [cite: 21]
        if (i > 0) {
            cout << endl;
        }
        solve_test_case();
    }

    return 0;
}