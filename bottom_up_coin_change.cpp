/*
Dynamic programming using bottom-up method
* The coin change problem
You want to split 18 cents into coins using the min number of coins from coins 1, 2, 5, 10
* State definition:
state i: the min number of coins to represent amount i
* State transition:
state m can transit to state n (m<n) by adding a single coin.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int c = 18;
    vector <int> w = {1, 2, 5, 10}, memo(c + 1, INT_MAX);
    memo[0] = 0;
    for (int i = 0; i <= c; i++) 
    for (int j = 0; j < w.size(); j++) if (i + w[j] <= c) memo[i + w[j]] = min(memo[i] + 1, memo[i + w[j]]);
    for (int a = 0; a < memo.size(); a++) cout << a << ": " << memo[a] << endl;
}
