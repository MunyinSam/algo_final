#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Coupon
{
    int value;
    int original_index;
};

bool compareCoupons(const Coupon a, const Coupon b)
{
    return a.value > b.value;
}

void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long W;

    if (!(cin >> N >> W))
        return;

    vector<Coupon> sorted_coupons(N);
    vector<int> final_counts(N, 0);

    for (int i = 0; i < N; ++i)
    {
        int value;
        cin >> value;
        sorted_coupons[i] = {value, i};
    }

    sort(sorted_coupons.begin(), sorted_coupons.end(), compareCoupons);

    for (int i = 0; i < N; ++i)
    {
        int value = sorted_coupons[i].value;
        int original_idx = sorted_coupons[i].original_index;

        if (W >= value)
        {
            int count = W / value;
            W -= (long long)count * value;
            final_counts[original_idx] = count;
        }

        if (W == 0)
        {
            break;
        }
    }
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