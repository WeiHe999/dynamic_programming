/*
problem: dynamic programming for grid travel
find the number of ways to travel from (0,0) to (N, N) with obstacles (e.g., aybales) in some cells
method: dynamic programming bottom up
input format:
1 # 1 test case
4 # 4*4 grid
...H
.H..
....
H...
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n;
    cin >> n;
    char a;
    vector <vector <char> > graph;
    vector <char> tmp;
    for (int x = 0; x < n; x++)
    {
        tmp = {};
        for (int y = 0; y < n; y++)
        {
            cin >> a;
            tmp.emplace_back(a);
        }
        graph.push_back(tmp);
    }
    vector <vector <int> > memo(n, vector <int>(n));
    memo[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j + 1 < n && graph[i][j + 1] == '.')
            {
                memo[i][j + 1] += memo[i][j];
            }
            if (i + 1 < n && graph[i + 1][j] == '.')
            {
                memo[i + 1][j] += memo[i][j];
            }
        }
    }
    cout << memo[n - 1][n - 1] << endl;
}
