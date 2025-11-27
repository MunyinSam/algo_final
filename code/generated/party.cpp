#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an LED
struct LED
{
    long long Y; // Height
    int C;       // Color
};

void solve()
{
    // N: number of LEDs (1 <= N <= 2,000)
    int N;
    if (!(cin >> N))
        return;

    // Read LED information (x-coordinate is implicit index 1 to N)
    vector<LED> leds(N);
    for (int i = 0; i < N; ++i)
    {
        if (!(cin >> leds[i].Y >> leds[i].C))
            return;
    }

    // Dynamic Programming Arrays:
    // dp_inc[i]: Max length of a valid sequence ending at led[i] with a NON-DECREASING height trend.
    // dp_dec[i]: Max length of a valid sequence ending at led[i] with a NON-INCREASING height trend.
    // We initialize all to 1, as a single LED is a valid sequence of length 1.
    vector<int> dp_inc(N, 1);
    vector<int> dp_dec(N, 1);

    int max_length = (N > 0) ? 1 : 0;

    // Iterate through all LEDs from the second one (i=1) up to N-1
    for (int i = 1; i < N; ++i)
    {
        // Current LED i: (Y_i, C_i)
        long long Yi = leds[i].Y;
        int Ci = leds[i].C;

        // Iterate through all preceding LEDs j < i
        for (int j = 0; j < i; ++j)
        {
            // Preceding LED j: (Y_j, C_j)
            long long Yj = leds[j].Y;
            int Cj = leds[j].C;

            // Condition: Consecutive LEDs must have different colors
            if (Cj != Ci)
            {
                // --- 1. Update dp_inc[i] (Non-decreasing trend ending at i) ---
                if (Yj <= Yi)
                { // Height is non-decreasing
                    // The sequence ending at j can be non-decreasing (dp_inc[j])
                    // or non-increasing (dp_dec[j]), as the trend can switch at i.
                    dp_inc[i] = max(dp_inc[i], 1 + dp_inc[j]);
                }

                // --- 2. Update dp_dec[i] (Non-increasing trend ending at i) ---
                if (Yj >= Yi)
                { // Height is non-increasing
                    // The sequence ending at j can be non-decreasing (dp_inc[j])
                    // or non-increasing (dp_dec[j]), as the trend can switch at i.
                    dp_dec[i] = max(dp_dec[i], 1 + dp_dec[j]);
                }
            }
        }

        // Update the overall maximum length found so far
        max_length = max(max_length, dp_inc[i]);
        max_length = max(max_length, dp_dec[i]);
    }

    // Output the result
    cout << max_length << endl;
}

int main()
{
    // Optimizations for fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}