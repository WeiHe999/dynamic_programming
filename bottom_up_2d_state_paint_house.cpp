/*
Dynamic programming using bottom-up method
* The house-painting problem
You want to paint 3 houses with color (Red or Blur or Green) at a minimal total cost , 
the consecutive houses cannot have the same color.

* 2-D State definition:
state (i, j): the minimal cost for painting i houses and the i-th house was painted with color j.
* State transition:
state (m1, n1) can transit to state (m2, n2) by painting a house with a color.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num_houses = 3, num_colors = 3;
    vector <vector <int> > costs = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
    vector <vector<int> > memo(num_houses+1, vector<int>(num_colors, INT_MAX));
    // the 1st house
    for (int j=0; j<num_colors; j++)
    {
        memo[1][j] = costs[0][j];
    }
    
    for (int i = 1; i < num_houses; i++)
    {
        for(int j=0; j<num_colors; j++)
        {
            // transit from current state (i, j) to the next state (i+1, k), and update the cost for state (i+1, k)
            for (int k=0; k<num_colors; k++)
            {
                // paint different color
                if (k!=j && memo[i][j] + costs[i+1-1][k] < memo[i+1][k]) 
                {
                    memo[i+1][k] = memo[i][j] + costs[i+1-1][k];
                }
            }
        }
    }
    
    cout << *min_element(memo[num_houses].begin(), memo[num_houses].end()) << endl;
}
