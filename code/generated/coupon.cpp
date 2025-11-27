#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// We use a struct to keep the coupon value and its original position together
struct Coupon
{
    int value;
    int original_index;
};

// Sort by value in descending order for the greedy approach
bool compareCoupons(const Coupon &a, const Coupon &b)
{
    return a.value > b.value;
}

void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long W; // W should be long long for large values

    if (!(cin >> N >> W))
        return;

    vector<Coupon> sorted_coupons(N);
    // This vector holds the final counts, mapped by the original index (0 to N-1)
    vector<int> final_counts(N, 0);

    for (int i = 0; i < N; ++i)
    {
        int value;
        cin >> value;
        sorted_coupons[i] = {value, i};
    }

    // Sort to apply the greedy algorithm correctly
    sort(sorted_coupons.begin(), sorted_coupons.end(), compareCoupons);

    // --- Corrected Greedy Logic ---
    for (int i = 0; i < N; ++i)
    {
        int value = sorted_coupons[i].value;
        int original_idx = sorted_coupons[i].original_index;

        if (W >= value)
        {
            // Calculate how many times this coupon can be used
            int count = W / value;

            W -= (long long)count * value;

            // Store the count directly into the final_counts vector at the correct original index
            final_counts[original_idx] = count;
        }

        if (W == 0)
            break;
    }

    // --- Corrected Output (in original index order) ---
    for (int i = 0; i < N; ++i)
    {
        cout << final_counts[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;
}

int main()
{
    solve();
    return 0;
}