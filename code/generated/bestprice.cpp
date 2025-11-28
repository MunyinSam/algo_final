#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Define a type for large prices
typedef long long Price;

// Function to solve the problem
void solve()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int W, L, A; // W: Width (rows), L: Length (cols), A: Min Area
    if (!(cin >> W >> L >> A))
        return;

    // The maximum possible price is 20*20 * 1,000,000 = 400,000,000.
    // We use long long for prices and the prefix sum table to be safe.

    // 1. Read the input grid P (0-based indexing)
    vector<vector<Price>> P(W, vector<Price>(L));
    for (int i = 0; i < W; ++i)
    {
        for (int j = 0; j < L; ++j)
        {
            cin >> P[i][j];
        }
    }

    // --- Step 1: Calculate 2D Prefix Sums (S) ---

    // S will be (W+1) x (L+1) for 1-based indexing lookup
    vector<vector<Price>> S(W + 1, vector<Price>(L + 1, 0));

    for (int i = 1; i <= W; ++i)
    {
        for (int j = 1; j <= L; ++j)
        {
            // Price P uses 0-based indices: P[i-1][j-1]
            // S uses 1-based indices
            S[i][j] = P[i - 1][j - 1] + S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
        }
    }

    // --- Step 2 & 3: Brute-Force Search for Optimal Rectangle ---

    // Initialize minimum price to a very large value
    Price min_price = numeric_limits<Price>::max();
    bool possible = false;

    // Iterate over all possible top-left corners (r1, c1)
    for (int r1 = 1; r1 <= W; ++r1)
    {
        for (int c1 = 1; c1 <= L; ++c1)
        {

            // Iterate over all possible bottom-right corners (r2, c2)
            for (int r2 = r1; r2 <= W; ++r2)
            {
                for (int c2 = c1; c2 <= L; ++c2)
                {

                    // Calculate the area of the current rectangle
                    long long current_area = (long long)(r2 - r1 + 1) * (c2 - c1 + 1);

                    // Check if the area constraint is met
                    if (current_area >= A)
                    {
                        possible = true;

                        // Calculate the price of the sub-rectangle in O(1)
                        // Price = S[r2][c2] - S[r1-1][c2] - S[r2][c1-1] + S[r1-1][c1-1]
                        Price current_price = S[r2][c2] - S[r1 - 1][c2] - S[r2][c1 - 1] + S[r1 - 1][c1 - 1];

                        // Update the minimum price found so far
                        min_price = min(min_price, current_price);
                    }
                }
            }
        }
    }

    // --- Output Result ---
    if (possible)
    {
        cout << min_price << "\n";
    }
    else
    {
        // If no rectangle of area >= A was found (though this is unlikely given constraints)
        // or if the constraints made it impossible to start the loop (A is very large, etc.)
        cout << -1 << "\n";
    }
}

int main()
{
    solve();
    return 0;
}