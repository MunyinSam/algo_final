#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// A very large number to represent infinity (unreachable amount)
const int INF = numeric_limits<int>::max();

void solve_test_case()
{
    int P; // Price in cents (P <= 10000)
    if (!(cin >> P))
        return;

    int N; // Number of denominations (N <= 100)
    if (!(cin >> N))
        return;

    vector<int> denominations(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> denominations[i];
    }

    // Determine a safe maximum amount for the DP array.
    // Max Price P is 10000. Max denomination is also up to 10000.
    // The total paid amount can be P + max_denomination - 1.
    // A safe limit is 20000.
    // We use 20001 for convenience (index up to 20000).
    const int MAX_AMOUNT = 20000;

    // dp[i] = minimum number of bills/coins required to make amount i exactly.
    // We use MAX_AMOUNT + 1 for array size to access indices 0 through MAX_AMOUNT.
    vector<int> dp(MAX_AMOUNT + 1, INF);

    // Base case: 0 coins for 0 cents
    dp[0] = 0;

    // 1. DP Transition: Build the table
    // Iterate through all available denominations (unlimited supply)
    for (int V : denominations)
    {
        // Iterate through all possible amounts
        for (int i = V; i <= MAX_AMOUNT; ++i)
        {
            // Check if amount i-V is reachable
            if (dp[i - V] != INF)
            {
                // Update dp[i] with the minimum number of coins
                // min(current dp[i], dp[i - V] + 1)
                dp[i] = min(dp[i], dp[i - V] + 1);
            }
        }
    }

    // 2. Finding the Optimal Solution
    int min_paid_amount = -1;
    int min_coins = INF;

    // Iterate starting from the price P up to the max amount.
    for (int A = P; A <= MAX_AMOUNT; ++A)
    {
        if (dp[A] != INF)
        {

            // Check if we found a better solution based on minimum coins.
            if (dp[A] < min_coins)
            {
                min_coins = dp[A];
                min_paid_amount = A;

                // IMPORTANT: We do not break here! We must continue iterating
                // to find a LARGER amount A that requires an even SMALLER number of coins.
                // The sample case demonstrates this:
                // Price=1400. If 1500 takes 2 coins and 2000 takes 1 coin,
                // 2000 (1 coin) would be the answer.
            }
            else if (dp[A] == min_coins)
            {
                // If the number of coins is the same, we prioritize the SMALLER amount paid.
                // Since we are iterating A in increasing order, min_paid_amount
                // already holds the smallest amount for this min_coins count.
                // So, we don't need to do anything here.
            }
            else
            {
                // Since we are looking for the *minimum* number of coins,
                // and we've already found min_coins, any subsequent amount A
                // that requires more coins (dp[A] > min_coins) can be ignored.
                // Furthermore, since the DP calculation only increases the coin count
                // (or keeps it the same) for larger amounts, the number of coins is
                // unlikely to suddenly drop lower at much larger A values.
                // However, to be fully safe, especially if the set of denominations is sparse,
                // we should check a reasonable range. Since MAX_AMOUNT is safe, we check the full range.
            }
        }
    }

    // Output the result
    cout << min_paid_amount << " " << min_coins << "\n";
}

int main()
{
    // Read the number of test cases
    int num_test_cases;
    if (!(cin >> num_test_cases))
        return 0;

    // Process each test case
    while (num_test_cases--)
    {
        solve_test_case();
    }

    return 0;
}