#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;
const int MAX_N = 100100;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int v[MAX_N];
    int a[MAX_N]; // best value
    int b[MAX_N]; // lastest best value

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    a[0] = 0;
    a[1] = 0;
    b[0] = 0;
    b[1] = 0;
    int best = 0;

    for (int i = 2; i < N; i++)
    {
        a[i] = v[i];

        if (i - 3 > 0)
        {
            a[i] += b[i - 3];
        }

        b[i] = b[i - 1];

        if (a[i] > b[i])
        {
            b[i] = a[i];
        }

        if (a[i] > best)
        {
            best = a[i];
        }
    }

    cout << best << endl;
}