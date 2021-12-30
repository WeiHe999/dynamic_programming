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
    vector <pair<int, int> > memo;
    for (auto x: vec1)
    {
       memo.push_back({x, x}); //{min, max} 
    }
    for (int i = 1; i < vec1.size(); i++)
    {
        // min
        int min_value = min( min(memo[i - 1].first * vec1[i], memo[i - 1].second * vec1[i]), memo[i].first);
        // max
        int max_value = max( max(memo[i - 1].first * vec1[i], memo[i - 1].second * vec1[i]), memo[i].second);
        memo[i] = {min_value, max_value};
    }
    int final_max = INT_MIN;
    for(auto x : memo)
    {
        if (x.second > final_max) final_max = x.second;
    }
    cout << final_max << endl;
}
