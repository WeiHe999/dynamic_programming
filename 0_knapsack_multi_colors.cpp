/*
dmoj: DMOPC '14 Contest 3 P6 - Not Enough Time!
Variant-2 (each item has three models with different weight and different value): 
you can select only one model for each item or do not select the item, select items to maximize the total value 
to be put into a knapsack with capacity of W.

key points:
1. use 1d memo vector
2. update n rounds on memo vector (n=number_items)
3. at round-k, update memo vector backward (from k=w to k=0)
*/


#include <bits/stdc++.h>
using namespace std;

template < typename T > void print (T t)
{
    for (const auto & e:t) cout << e << " ";
    cout << "\n";
}

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    long long n, t, s = 0;
    cin >> n >> t;
    vector <vector <long long> > weights(n + 1, vector <long long>(4)), values(n + 1, vector <long long>(4));
    for (long long x = 1; x <= n; x++) cin >> weights[x][1] >> values[x][1] >> weights[x][2] >> values[x][2] >> weights[x][3] >> values[x][3];
    vector <long long> memo(t + 1, -1);
    memo[0] = 0;
    for (long long j = 1; j <= n; j++)
    {
        for (long long i = t; i >=0 ; i--)
        {
            if (memo[i] == -1) continue;
            if (i + weights[j][1] <= t) memo[i + weights[j][1]] = max(memo[i] + values[j][1], memo[i + weights[j][1]]);
            if (i + weights[j][2] <= t) memo[i + weights[j][2]] = max(memo[i] + values[j][2], memo[i + weights[j][2]]);
            if (i + weights[j][3] <= t) memo[i + weights[j][3]] = max(memo[i] + values[j][3], memo[i + weights[j][3]]);
        }
    }
    for (auto x : memo) s = max(x, s);
    cout << s << "\n";
}
