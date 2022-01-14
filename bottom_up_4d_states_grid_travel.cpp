/*
problem: dynamic programming for grid travel
find the number of ways to travel from (0,0) to (N, N) with obstacles (e.g., aybales) in some cells

method: dynamic programming bottom up

input format:
1
4 3
...H
.H..
....
H...
*/



#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.sync_with_stdio (0);
    cin.tie (0);
    int t, n, tot_turns;
    cin >> t;
    char a;
    for (int x = 0; x < t; x++)
    {
        vector <vector <char> > graph;
        vector <char> tmp;
        cin >> n >> tot_turns;
        for (int i = 0; i < n; i++)
        {
            tmp = {};
            for (int j = 0; j < n; j++)
            {
                cin >> a;
                tmp.emplace_back(a);
            }
            graph.push_back(tmp);
        }
        // for (auto b : graph)
        // {
        //     for (auto c : b) cout << c;
        //     cout << endl;
        // }
        
        //state matrix: dp[r][c][k][f] represent the number of ways ending at (r, c) with k turns and facing f
        // facing 0 means toward-east, facing 1 means toward-south
        int dp[50][50][tot_turns+1][2];
        memset(dp, 0, sizeof dp); // initialize to 0
        //initialization
        dp[0][0][0][0] = 1; //facing east
        dp[0][0][0][1] = 1; // facing south
        
        // fill in states
        for (int r=0; r<n; r++)
        {
            for(int c=0; c<n; c++)
            {
                for(int k=0; k<=tot_turns; k++)
                {
                    
                    // case 1: currently facing east
                    if(dp[r][c][k][0]>0)
                    {
                        // case 1-1: continue east: to (r, c+1), no turn
                        if (c+1 < n && graph[r][c+1]=='.')
                        {
                            // state transition
                            dp[r][c+1][k][0] += dp[r][c][k][0];
                        }
                        
                        //case 1-2: turn south: to (r+1, c)
                        if (r+c>0 && r+1 < n && graph[r+1][c]=='.' && k+1 <= tot_turns)
                        {
                            // state transition
                            dp[r+1][c][k+1][1] += dp[r][c][k][0];
                        }
                    }
                    
                    // case 2: currently facing south
                    if(dp[r][c][k][1]>0)
                    {
                        // case 2-1: continue south: to (r+1, c), no turn
                        if (r+1<n && graph[r+1][c]=='.')
                        {
                            // state transition
                            dp[r+1][c][k][1] += dp[r][c][k][1];
                        }
                        
                        //case 2-2: go east: to (r, c+1), turn (exception for going east from (0,0))
                        if (r+c>0 && c+1<n && graph[r][c+1]=='.' && k+1<=tot_turns)
                        {
                            // state transition
                            dp[r][c+1][k+1][0] += dp[r][c][k][1];
                        }
                    }                    
                    
                }
            }
        }
        
    
        // calculate the number of ways at the destination
        int ans = 0;
        for(int k=0; k<=tot_turns; k++)
        {
            for (int f=0; f<2; f++)
            {
                ans += dp[n-1][n-1][k][f];
            }
        }
        cout << ans << endl;

    }
}
