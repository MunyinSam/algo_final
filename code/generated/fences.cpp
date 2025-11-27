#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a house
struct House
{
    long long S, T;
};

void solve()
{
    // N: number of houses (2 <= N <= 100,000) [cite: 29]
    // L: fixed fence length (1 <= L <= 10,000) [cite: 5, 29]
    int N;
    long long L;

    // Read N and L from the first line of input [cite: 29]
    if (!(cin >> N >> L))
        return;

    // Read house positions S_i and T_i
    vector<House> houses(N);
    for (int i = 0; i < N; ++i)
    {
        // T_i <= 1,000,000,000 [cite: 30]
        if (!(cin >> houses[i].S >> houses[i].T))
            return;
    }

    // --- Greedy Algorithm ---
    int fence_count = 0;
    int current_house_index = 0;

    // Loop until all houses are covered
    while (current_house_index < N)
    {
        // 1. House 'i' is the first uncovered house.
        // We must place a new fence to cover it completely.

        // House 'i' spans [S_i, T_i]
        long long Si = houses[current_house_index].S;

        // 2. Increment the total fence count
        fence_count++;

        // 3. Apply the greedy choice:
        // Place the fence at the latest possible position 'X' that covers house 'i'.
        // The valid range is T_i - L <= X <= S_i.
        // The largest possible X is S_i.

        // Fence position starts at X = S_i, covering the segment [S_i, S_i + L]
        long long fence_end_position = Si + L;

        // 4. Determine how many subsequent houses this new fence covers.
        int next_uncovered_house_index = current_house_index;

        // Iterate through houses starting from the current one.
        // A house 'j' at [S_j, T_j] is completely covered if:
        // Fence_start_position <= S_j (which is true since we start at S_i)
        // AND T_j <= Fence_end_position (T_j <= S_i + L)

        while (next_uncovered_house_index < N)
        {
            long long Tj = houses[next_uncovered_house_index].T;

            if (Tj <= fence_end_position)
            {
                // This house is covered completely by the current fence.
                next_uncovered_house_index++;
            }
            else
            {
                // This house (or any subsequent house) is NOT covered.
                break;
            }
        }

        // Move the pointer to the first house NOT covered by the current fence.
        current_house_index = next_uncovered_house_index;
    }

    // Output the minimum number of fences needed [cite: 33]
    cout << fence_count << endl;
}

// In a real competitive programming environment, you would use:
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     solve();
//     return 0;
// }
// For simplicity and standard output, we just use main
int main()
{
    solve();
    return 0;
}