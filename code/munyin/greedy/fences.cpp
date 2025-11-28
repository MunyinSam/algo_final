#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// Define a struct for a house
struct House
{
    long long S; // Start position
    long long T; // End position
};

void solve()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;       // Number of houses (up to 100,000)
    long long L; // Fixed fence length (up to 10,000)

    // Read N and L
    if (!(cin >> N >> L))
        return;

    // Houses are already given in order of their start positions.
    vector<House> houses(N);

    // Read all house coordinates [S_i, T_i]
    for (int i = 0; i < N; ++i)
    {
        if (!(cin >> houses[i].S >> houses[i].T))
            return;
    }

    // --- Greedy Algorithm Implementation ---

    int fence_count = 0;
    int i = 0; // Index of the first uncovered house

    while (i < N)
    {
        // 1. Identify the current house (i) that must be covered.
        const House &current_house = houses[i];

        // 2. Place the fence optimally:
        // Start the fence at S_i to maximize its reach to the right.
        long long fence_start_X = current_house.S;
        long long fence_end_X = fence_start_X + L;

        // Increment the fence count
        fence_count++;

        // 3. Count and skip all houses covered by this new fence.
        // A house j is completely covered if its end T_j is <= fence_end_X.

        // We start checking from the current house i, which we know is covered.
        int j = i;
        while (j < N)
        {
            // Check if house j is completely covered: T_j <= X + L
            if (houses[j].T <= fence_end_X)
            {
                j++; // House j is covered, move to the next house
            }
            else
            {
                // House j is not covered by the current fence, so this is where
                // the next fence must start.
                break;
            }
        }

        // Update the index of the next uncovered house.
        // The loop finished, so house j is the first one that was NOT covered.
        i = j;
    }

    // Output the result
    cout << fence_count << "\n";
}

int main()
{
    // The problem implies a single run on the entire input,
    // without multiple test cases specified by a header number.
    solve();

    return 0;
}