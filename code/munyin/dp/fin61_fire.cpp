#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, R;
    cin >> N >> R;
    int const MAX_N = 100000;

    int X[MAX_N];

    for (int i = 0; i < N; i++)
    {
        cin >> X[i];
    }

    int A[MAX_N];
    int B[MAX_N];

    // A is the starting garage range
    A[0] = X[0];
    B[0] = X[0];

    int firestation = 1;
    int start = A[0];

    for (int i = 1; i < N; i++)
    {

        if (X[i] - start > R*2)
        {
            A[i] = X[i];
            cout << "print " << A[i] << endl;
            start = A[i];
            firestation++;
        }
        else
        {
            A[i] = A[i - 1];
        }
    }
    cout << firestation << endl;
}