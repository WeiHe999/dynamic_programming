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

int main() {
    // amount
    int amount = 28;
    // list of coins
    vector<int> coins = {1, 2, 5, 10};
    // memo to store: state-i: max_value
    unordered_map<int, int> memo;
    memo[0] = 0;
    for (int i=0; i<=amount; i++)
    {
        for (int j=0; j<coins.size(); j++)
        {
            if (i + coins[j] <= amount)
            {
                // state transition from bottom to upper by adding a single item, choose the max value
                if (memo[i + coins[j]] > 0) memo[i + coins[j]] = min(memo[i] + 1, memo[i + coins[j]]);
                else memo[i + coins[j]] = memo[i] + 1;
            }
        }
    }
    cout << memo[amount] << endl;
}
