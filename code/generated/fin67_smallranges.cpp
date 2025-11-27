#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the problem
void solve()
{
    // Read N and L
    long long N_ll, L;
    // We use long long for N initially because the problem statement
    // uses it in the input description (even though N <= 200,000 fits in int).
    // L must be long long due to its large possible value (up to 1,000,000,000).
    if (!(cin >> N_ll >> L))
        return;

    // Cast N to int for array size/looping since N <= 200,000.
    int N = (int)N_ll;

    // Read the prices. Prices (Xi) can be up to 1,000,000,000,
    // so we must use long long.
    vector<long long> prices(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> prices[i];
    }

    // 1. Sort the prices (O(N log N))
    sort(prices.begin(), prices.end());

    // 2. Sliding Window (O(N))

    // 'left' pointer for the cheapest item in the current window
    int left = 0;
    // 'max_items' to store the maximum length found
    int max_items = 0;

    // 'right' pointer iterates over all items, representing the most expensive item
    for (int right = 0; right < N; ++right)
    {
        // While the difference is too large, shrink the window from the left
        // prices[right] is the max price, prices[left] is the min price
        while (prices[right] - prices[left] > L)
        {
            left++;
        }

        // At this point, the window [left...right] satisfies the condition:
        // prices[right] - prices[left] <= L

        // Calculate the current number of items in the window
        // The length is right - left + 1
        int current_length = right - left + 1;

        // Update the maximum number of items
        max_items = max(max_items, current_length);
    }

    // Output the result
    cout << max_items << endl;
}

// Main function
int main()
{
    // Optimization for faster input/output operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}