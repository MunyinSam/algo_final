#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LED
{
    long long Y; // Height
    int C;       // Color
};

void solve()
{
    int N;
    if (!(cin >> N))
    {
        return;
    }

    vector<LED> leds(N);

    for (int i = 0; i < N; ++i)
    {
        if (!(cin >> leds[i].Y >> leds[i].C))
        {
            return;
        }
    }

    vector<int> dp_inc(N, 1);
    vector<int> dp_dec(N, 1);

    int max_length = (N > 0) ? 1 : 0;

    for (int i = 1; i < N; ++i)
    {
        long long Yi = leds[i].Y;
        int Ci = leds[i].C;
        for (int j = 0; j < i; ++j)
        {
            long long Yj = leds[j].Y;
            int Cj = leds[j].C;

            if (Cj != Ci)
            {
                if (Yj <= Yi)
                {
                    dp_inc[i] = max(dp_inc[i], 1 + dp_inc[j]);
                }

                if (Yj >= Yi)
                {
                    dp_dec[i] = max(dp_dec[i], 1 + dp_dec[j]);
                }
            }
        }
        max_length = max(max_length, dp_inc[i]);
        max_length = max(max_length, dp_dec[i]);
    }

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