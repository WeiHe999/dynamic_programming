/*
Dynamic programming using bottom-up method
* The Maximum Product Subarray problem
Find the max product of the consecutive sub-array from an interger array {2, -3, -2, 4, -5, -5, -5}

* 1-D State definition:
state-i: the max product of the consecutive sub-array ending at the i-th element

* State transition:
State-m can transit to state-(m+1)
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector <int> vec1 = {2, -3, -2, 4, -5, -5, -5};
    vector <pair <int, int> > memo;
    for (auto x : vec1) memo.push_back({x, x});
    for (int i = 1; i < vec1.size(); i++)
    {
        int a = min(min(memo[i - 1].first * vec1[i], memo[i - 1].second * vec1[i]), memo[i].first);
        int b = max(max(memo[i - 1].first * vec1[i], memo[i - 1].second * vec1[i]), memo[i].second);
        memo[i] = {a, b};
    }
    int max = INT_MIN;
    for (auto a : memo) if (a.second > max) max = a.second;
    cout << max << endl;
}
