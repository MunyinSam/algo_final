#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;
const int MAX_N = 1010;
int dp[MAX_N];


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;
    dp[0] = 1;

    for (int i = 1; i <= N; i++)
    {
        for (int j = i - 1; j >= i - 1 - K; j--)
        {
            if (j >= 0)
            {
                dp[i] += dp[j];
                dp[i] %= 9377;
            }
        }
    }

    cout << dp[N] << endl;;
}