#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <numeric>

using namespace std;

// Define the modulus value
// The problem asks for the answer modulo 7919.
const int MOD = 7919;

void solve()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // N: number of bottles, M: number of people (requests)
    int N, M;
    if (!(cin >> N >> M))
        return;

    // Use a max-heap (priority_queue) to store the water levels.
    // This allows us to quickly access the bottle with the largest amount of water.
    priority_queue<long long> water_levels;

    // 1. Read the initial water levels (L_i)
    for (int i = 0; i < N; ++i)
    {
        long long L;
        cin >> L;
        water_levels.push(L);
    }

    // sol: Stores the total amount of water carried, modulo MOD.
    // Note: The total carried water can be large, but the running sum 'sol'
    // is kept modulo 7919, as suggested by the problem notes.
    long long sol = 0;

    // 2. Process the M requests
    for (int i = 0; i < M; ++i)
    {
        // J: index of the bottle to return water to (1-indexed)
        // D: amount of water the person decides to drink
        int J;
        long long D;
        if (!(cin >> J >> D))
            return;

        // --- Step 2a: Find and process the largest bottle ---

        // Check if there are any bottles left.
        if (water_levels.empty())
        {
            // No bottles left to drink from.
            // Since D <= 1,000,000,000, the total amount carried will only be 0
            // if all bottles are empty when the first person requests water.
            // The person just drinks D from the "largest bottle" which is empty.
            // This case might be tricky if the heap is empty, but generally
            // for the problem constraints, we should assume the heap might become
            // empty during the process if all water is drunk.
            // Since we can't access a bottle to drink from, we skip to the return step.

            // To be safe, we'll assume the problem guarantees enough bottles
            // or that the "largest" is conceptually 0 if the heap is empty.
            // If the heap is empty, there is no water to drink.

            // For now, let's proceed assuming the drinking step only happens if the heap is not empty.
            // If it is empty, the amount drunk will be 0.
            // For the sake of following the logic: If the person *can't* drink,
            // the problem states "that happens, that person will not complain but will just
            // drink all the available water." Available water is 0.

            // We'll skip the drink part and proceed to the return part.
        }
        else
        {
            // Get the water level of the largest bottle
            long long largest_water = water_levels.top();
            water_levels.pop();

            // Calculate the amount of water drunk (X)
            // The person drinks min(D, largest_water)
            long long X = min(D, largest_water);

            // Calculate the remaining water in the bottle
            long long remaining_water = largest_water - X;

            // --- Step 2b: Update the total carried water (sol) ---
            // Add the amount drunk (X) to the total 'sol' and apply modulo.
            // The note says: sol = (sol + X) % MOD
            sol = (sol + X) % MOD;

            // --- Step 2c: Return the remaining water to bottle J ---
            // The problem uses 1-based indexing for J, but since we are using
            // a max-heap and not a fixed-size array/vector to track bottles,
            // we treat J as a conceptual "placeholder" for where the remaining
            // water *would* go. The crucial part is adding the remaining water
            // back into the pool of available bottles if it's > 0.

            // The 'J' index is a red herring in the context of the max-heap implementation;
            // we simply add the remaining water back into the heap to be considered later.

            if (remaining_water > 0)
            {
                water_levels.push(remaining_water);
            }
        }

        // --- Step 2d: The person returns the bottle (J) and we must update its water level. ---
        // The problem description says: "The next N lines describe the initial amount of water...
        // The next M lines describe the information on the people requesting the water.
        // For 1<=i<=M, line 1+N+i contains an integer Dj, the amount of water person j
        // decides to drink (1<=Dj<=1,000,000,000)."

        // CRUCIAL MISINTERPRETATION FIX:
        // The problem *does not* state that the person returns the *same* bottle they drank from.
        // The problem states:
        // 1. "person will pick the bottle with the **largest** amount of water to the person." (Drinking)
        // 2. "The next M lines... line 1+N+i contains an integer Dj, the amount of water person j
        //    decides to drink (1<=Dj<=1,000,000,000)."
        //    Wait, the input is J (bottle index) and D (amount to drink).
        //    Let's re-read the input structure:
        //    Input:
        //    - N M
        //    - N lines of L_i (initial water)
        //    - M lines of J D (request)

        // This implies that J is the index of the bottle the person returns/adds water to.
        // Since we are using a max-heap, we don't track fixed indices (1...N).
        // The crucial realization is that the problem *must* mean that the person returns *a* // bottle with a certain level, but its *identity* (J) is only for context
        // in an array-based solution. In a heap-based solution, we simply add the new level
        // into the pool.

        // Let's re-examine the Example:
        // Initial: 20, 15, 13, 10, 6, 50, 4. (N=7)
        // 1st request (J=5, D=3):
        // - Largest: 50. Drink min(3, 50) = 3. Carried: 3.
        // - Remaining: 50 - 3 = 47.
        // - Return (to J=5): The problem *doesn't* specify the level returned.
        //   It says "The next N lines describe the initial amount of water in each bottle. More specifically, line 1 + i contains an integer L_i".
        //   Then "The next M lines describe the information on the people requesting the water. For 1<=i<=M, line 1+N+i contains an integer Dj, the amount of water person j decides to drink (1<=Dj<=1,000,000,000)."

        // The example explanation is the key:
        // 1st: Person gets **50** (bottle), drinks 3. Remaining: 47. **Carried: 3**.
        //   Bottles: 20, 15, 13, 10, 6, 47, 4.
        // 2nd: Person gets **47** (bottle), drinks 10. Remaining: 37. **Carried: 3 + 10 = 13**.
        //   Bottles: 20, 15, 13, 10, 6, 37, 4.
        // 3rd: Person gets **37** (bottle), drinks 5. Remaining: 32. **Carried: 13 + 5 = 18**.
        //   Bottles: 20, 15, 13, 10, 6, 32, 4.

        // OK, I've got it. The input `J` (bottle index) is **IRRELEVANT** for the logic of finding the largest and drinking.
        // It's a distractor/legacy from an array-based approach. We only care about:
        // 1. Finding $\max(\text{water levels})$.
        // 2. $\text{Amount drunk} = \min(D, \max(\text{water levels}))$.
        // 3. $\text{Total carried} += \text{Amount drunk}$.
        // 4. $\text{Remaining water} = \max(\text{water levels}) - \text{Amount drunk}$.
        // 5. If $\text{Remaining water} > 0$, put it back in the pool.

        // The variable `J` in the input line `J D` should be ignored.

        // Re-implementing the logic based on this confirmed understanding:

        // Check if there's any water available.
        if (!water_levels.empty())
        {
            // 1. Get the largest bottle
            long long largest_water = water_levels.top();
            water_levels.pop();

            // 2. Amount drunk (X)
            long long X = min(D, largest_water);

            // 3. Update total carried water (sol)
            sol = (sol + X) % MOD;

            // 4. Calculate remaining water
            long long remaining_water = largest_water - X;

            // 5. Put remaining water back if positive
            if (remaining_water > 0)
            {
                water_levels.push(remaining_water);
            }
        }
    }

    // 3. Output the result
    cout << sol << "\n";
}

int main()
{
    solve();
    return 0;
}