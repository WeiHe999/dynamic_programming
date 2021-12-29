/*
Dynamic programming using bottom-up method
* The house-painting problem
You want to paint 3 houses with color (Red or Blue or Green) at a minimal total cost.
Any consecutive houses cannot have the same color.

* 2-D State definition:
state (i, j): the minimal cost for painting i houses and the i-th house was painted with color j.
* State transition:
state (i, j) can transit to state (i+1, k) by painting a house with a color.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num_houses = 3, num_colors = 3;
    vector <vector <int> > costs = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}}, memo(num_houses + 1, vector <int>(num_colors, INT_MAX));
    for (int a = 0; a < num_colors; a++) memo[1][a] = costs[0][a];
    for (int i = 1; i < num_houses; i++)
    {
        for (int j = 0; j < num_colors; j++)
        {
            for (int k = 0; k < num_colors; k++)
            {
                if (k != j)
                {
                    memo[i + 1][k] = min(memo[i][j] + costs[i][k], memo[i + 1][k]);
                }
            }
        }
    }
    cout << *min_element(memo[num_houses].begin(), memo[num_houses].end()) << endl;
}
