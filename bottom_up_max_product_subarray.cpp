/*
Dynamic programming using bottom-up method
* The Maximum Product Subarray problem
Find the max product of the consecutive sub-array from an interger array [2, 3, -2, 4]

* 1-D State definition:
state-i: the max product of the consecutive sub-array ending at the i-th element

* State transition:
State-m can transit to state-(m+1)
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {2, 3, -2, 4}, memo;
    memo.assign(arr.begin(), arr.end());
    for(int i=1; i<arr.size(); i++)
    {
        memo[i] = max(memo[i-1]*arr[i], memo[i]);
    }
    cout << *max_element(memo.begin(), memo.end());
    
}
