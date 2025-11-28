#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

struct Demand
{
    long long a;
    long long b;
};

bool compareDemands(const Demand &d1, const Demand &d2)
{
    if (d1.b != d2.b)
    {
        return d1.b < d2.b; // Sort by earliest end time (b)
    }
    return d1.a < d2.a;
}

void solve()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N; // Total number of gems (up to 10^9) - we only need it for context.
    int M;       // Total number of demands (up to 100,000)

    if (!(cin >> N >> M))
        return;

    vector<Demand> demands(M);

    for (int i = 0; i < M; i++)
    {
        if (!(cin >> demands[i].a >> demands[i].b))
            return;
    }

    sort(demands.begin(), demands.end(), compareDemands);

    int satisfied_demands_count = 0;

    long long last_end_position = 0;

    for (const auto &demand : demands)
    {
        if (demand.a > last_end_position)
        {
            // Select this demand
            satisfied_demands_count++;

            // Update the end position of the last selected demand
            last_end_position = demand.b;
        }
    }

    cout << satisfied_demands_count << "\n";
}

int main()
{

    solve();

    return 0;
}