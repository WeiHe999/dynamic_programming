/*
Dynamic programming using bottom-up method
* The Square Sum problem
Given an integer, find the min number of perfect square numbers that sum to it

* 1-D State definition:
state-i: the min number of square numbers that sum to i

* State transition:
State-m can transit to state-n if n = m + k^2 (k=1, 2, 3, .....)
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 324;
    vector <int> memo(n + 1, INT_MAX);
    memo[0] = 0;
    for (int x = 0; x <= n; x++)
    {
        int a = 1;
        while (true)
        {
            if (x + pow(a, 2) <= n) memo[x + pow(a, 2)] = min(memo[x] + 1, memo[x + pow(a, 2)]);
            else break;
            a++;
        }
    }
    cout << memo[n] << endl;
}
