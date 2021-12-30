/*
Dynamic programming using bottom-up method
* The longest increasing subsequence problem
Find the length of the longest increasing subsequence from an interger array [7, 2, 4, 3, 9, 8]

* 1-D State definition:
state-i: the length of the longest increasing subsequence ending at the i-th digit

* State transition:
State-m can transit to state-n if the n-th digit is larger than the m-th digit
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> v = {7, 2, 4, 3, 9, 8};
    vector <int> memo(v.size() + 1, 1);
    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = i+1; j <= v.size(); j++)
        {
            if (v[j-1] > v[i-1])
            {
                memo[j] = max(memo[i] + 1, memo[j]);
            }
        }
    }
    
    cout << *max_element(memo.begin(), memo.end()) << endl;
}
