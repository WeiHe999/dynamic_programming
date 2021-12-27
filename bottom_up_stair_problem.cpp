/*
Dynamic programming using bottom-up method
* The stair problem
You want to step to 19th step, each time you can go 1, 2, or 3 steps (3 options), find the number of ways to reach it.
* State definition:
state i: the number of ways to get to the destination.
* State transition:
state m can transit to state n (m<n) by selecting one option.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int c = 19;
    vector <int> w = {1, 2, 3}, memo(c + 1, 0);
    memo[0] = 1;
    for (int i = 0; i <= c; i++) for (int j = 0; j < w.size(); j++) if (i + w[j] <= c) memo[i + w[j]] += memo[i];
    for (int a = 0; a < memo.size(); a++) cout << a << ": " << memo[a] << endl;
}
