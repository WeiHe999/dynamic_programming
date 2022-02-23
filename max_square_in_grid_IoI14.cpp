/*
IOI '14 - Taipei, Taiwan
Cutting a square from a material
Jian-Jia has a piece of metal material and he wants to cut a square out of it. The material consists of  by  
unit grids and Jian-Jia can only cut the material along grid boundary. Each grid is either usable or defective, 
and Jian-Jia wants to cut the largest possible square from the material without any defective grids. After determining 
the maximum size of the square, Jian-Jia also wants to know how many ways he can cut the largest square from this material. 
Finally Jian-Jia will report the product of the maximum size and the number of possible ways.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, a;
    cin >> n;
    vector <vector <int> > grid(n, vector <int>(n));
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            cin >> a;
            grid[x][y] = a;
        }
    }
    int maxa = INT_MIN, maxn = 0;
    for (int b = 0; b < grid.size(); b++)
    {
        for (int c = 0; c < grid[0].size(); c++)
        {
            if (b != 0 && c != 0)
            {
                if (grid[b][c] == 0) continue;
                grid[b][c] = min(min(grid[b - 1][c], grid[b - 1][c - 1]), grid[b][c - 1]) + 1;
            }
            if (maxa < grid[b][c])
            {
                maxa = grid[b][c];
                maxn = 0;
            }
            if (maxa == grid[b][c]) maxn++;
        }
    }
    cout << maxa * maxn << endl;
}
