/*
Dynamic programming using bottom-up method
* The longest common substring problem
Find the length of the longest common substring between string A and string B
where string_a = "abcde", string_b="ace"

* 2-D State definition:
state (i, j): the length of the longest common substring between string_a[:i] and sting_b[:j]

* State transition:
if string_a[i] != string_b[j], then state (i, j) = max(state(i-1, j), state(i, j-1))
else state (i, j) = state(i-1, j-1) + 1
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a = "abcde", b = "ace";
    vector <vector <int> > memo(b.size() + 1, vector <int>(a.size() + 1));
    for (int i = 1; i <= b.size(); i++)
    {
        for (int j = 1; j <= a.size(); j++)
        {
            if (b[i - 1] == a[j - 1]) memo[i][j] = memo[i - 1][j - 1] + 1;
            else memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
        }
    }
    cout << memo[b.size()][a.size()] << endl;
}
