#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L;

    if (!(cin >> N >> L))
    {
        return;
    }

    vector<pair<long long, long long>> houses(N);

    for (int i = 0; i < N; i++)
    {
        cin >> houses[i].first >> houses[i].second;
    }

    int fence_count = 0;
    int i = 0;
    while (i < N)
    {
        long long S_current = houses[i].first;
        fence_count++;
        long long reach_limit = S_current + L; 

        while (i < N && houses[i].first <= reach_limit)
        {
            i++;
        }
    }

    cout << fence_count << endl;
}

int main()
{
    solve();
    return 0;
}