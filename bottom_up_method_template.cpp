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

int main()
{
    int c = 5;
    vector <int> w = {1, 2, 3}, v = {8, 15, 25}, memo(c + 1, 0);
    for (int i = 0; i <= c; i++) for (int j = 0; j < w.size(); j++) if (i + w[j] <= c) memo[i + w[j]] = max(memo[i] + v[j], memo[i + w[j]]);
    for (int a = 0; a < memo.size(); a++) cout << a << ": " << memo[a] << endl;
}
