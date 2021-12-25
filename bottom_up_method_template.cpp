/*
Dynamic programming using bottom-up method
* The knapsack problem
The capacity of te knapsack is 5 kg, there are following items:
Item A: weight = 1 kg, value = $8
Item B: weight = 2 kg, value = $15
Item C: weight = 3 kg, value = $25
Find the max value that the knapsack can store.
* State definition:
state i: the max value that can be stored with the knapsack of capacity i kg
* State transition:
state m can transit to state n (m<n) by adding a single item.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // knapsack capacity
    int cap = 5;
    // list of item weights
    vector<int> weights = {1, 2, 3};
    // list of item values
    vector<int> values = {8, 15, 25};
    // Vector memo to store state info
    vector<int> memo(cap+1, 0); //initialize to 0
    memo.push_back(0);
    for (int i=0; i<=cap; i++)
    {
        for (int j=0; j<weights.size(); j++)
        {
            if (i + weights[j] <= cap)
            {
                // state transition from bottom to upper by adding a single item, choose the max value
                if (memo[i + weights[j]] > 0) memo[i + weights[j]] = max(memo[i] + values[j], memo[i + weights[j]]);
                else memo[i + weights[j]] = memo[i] + values[j];
            }
        }
    }
    cout << memo[cap] << endl;
}
