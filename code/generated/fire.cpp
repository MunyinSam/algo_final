#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // 1. Optimization for faster I/O
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, R;
    if (!(cin >> N >> R))
        return 0;

    // 2. Use Vector instead of fixed array (Safer memory management)
    vector<int> X(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i];
    }

    // 3. Logic (Greedy)
    int firestations = 1;
    int start_pos = X[0]; // effectively the start of the current covered range

    for (int i = 1; i < N; i++)
    {
        // If the current garage is further than the diameter (2*R)
        // from the start of the current coverage:
        if (X[i] - start_pos > R * 2)
        {
            // We need a new station.
            // This garage becomes the start of the new coverage range.
            start_pos = X[i];
            firestations++;
        }
    }

    cout << firestations << endl;
    return 0;
}