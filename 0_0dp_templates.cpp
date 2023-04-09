/**************************************************************************************
***************** Knapsack DP **************************************************
**************************************************************************************/

## main #####
int main()
{
    long long time_limit, weigh_capacity, num_items, weight, value, time1;
    vector< vector<long long> > items;
    cin >> time_limit >> weigh_capacity >> num_items;
    for (long long i = 0; i < num_items; i++)
    {
        cin >> value >> time1 >> weight;
        items.push_back({weight, time1, value, 1});
    }
}

/***************** Generic mixed Knapsack **********************************/
/*
This function converts items with limited amount to 0/1 items, form example, item_1 has weight 4, value 5, can
be used 3 times, denoted as {4, 5, 3}, can be converted to 2 0/1 items {{4, 5, 1}, {4*2, 5*2, 2}}
the output is stored in vector<vector<long long> > new_items
*/

void convert_knapsack_items(vector<vector<long long> > items, vector<vector<long long> > &new_items)
{
    new_items = {};
    for (long long i = 0; i < items.size(); i++)
    {
        vector<long long> cur_item = items[i];
        long long amount = cur_item[2], weight = cur_item[0], value = cur_item[1], power = 0;
        if (amount < 2) 
        {
            new_items.push_back(cur_item);
            continue;
        }
        while (amount > 0)
        {
            long long split_amount = pow(2, power);
            new_items.push_back({weight * min(split_amount, amount), value * min(split_amount, amount), 1});
            amount -= split_amount;
            power++;
        }
    }    
}


/* each knapsack has capacity of weight_capacity
each item has n levels, each level can be done at most 1 time (category=1) or unlimited times (category=-1)
items are put long longo a vector as below:
items ={ {item_1_weight, item_1_value, item_1_categoty}, {item_2_weight, item_2_value, item_2_categoty}} 
category: 1 is 0/1 knapsack, -1 is unlimited knapsack
 */
long long knapsack(vector<vector<long long> > items, long long weight_capacity)
{
    long long num_items = items.size();
    vector<long long> memo(weight_capacity + 1, -1);
    memo[0] = 0;
    // update
    for (long long i = 0; i < num_items; i++)
    {
        long long weight = items[i][0], value = items[i][1], category = items[i][2];
        if (category==1)
        {
            // 0/1 knapsack, backward update
            for (long long k = weight_capacity; k >= 0; k--)
            {
                if (memo[k]==-1) continue;
                if (k + weight <= weight_capacity) 
                {
                    memo[k + weight] = max(memo[k + weight], memo[k] + value);
                }
            }                
        }
        else
        {
            // unlimited knapsack, forward update
            for (long long k = 0; k <= weight_capacity; k++)
            {
                if (memo[k]==-1) continue;
                if (k + weight <= weight_capacity) 
                {
                    memo[k + weight] = max(memo[k + weight], memo[k] + value);
                }
            }                  
        }
        // cout << "memo state " << endl;
        // print(memo);
    }
    long long max_value = -1;
    for (long long k=0; k <= weight_capacity; k++)
    {
        max_value = max(max_value, memo[k]);
    }
    return max_value;
}

/***************** Conditonal Knapsack **********************************/
/* each knapsack has capacity of weight_capacity
each item has n levels, each level can be done at most 1 time (category=1) or unlimited times (category=-1)
items are put into a vector as below:
    items ={ {item_1_level_1_weight, item_1_level_1_value, item_1_level_1_categoty, 
    item_1_level_2_weight, item_1_level_2_value, item_1_level_2_categoty}, 
    {item_2_level_1_weight, item_2_level_1_value, item_2_level_1_categoty}} 
    category: 1 is 0/1 knapsack, -1 is unlimited knapsack
 */

long long conditional_knapsack(vector<vector<long long> > items, long long num_items, long long num_levels, long long weight_capacity)
{
    vector<vector<long long> > memo(num_levels + 1, vector<long long>(weight_capacity + 1, -1));
    memo[0][0] = 0;
    // update
    vector<long long> vec_max = memo[0];
    for (long long i = 0; i < num_items; i++)
    {
        for (long long j=0; j< items[i].size(); j+=3)
        {
            long long level_id = j/3, weight = items[i][j], value = items[i][j+1], category = items[i][j+2];
            //cout << "weight=" << weight << ", value=" << value << ", category=" << category << endl;
            if (category==1)
            {
                // 0/1 knapsack, backward update
                for (long long k = weight_capacity; k >= 0; k--)
                {
                    if (memo[level_id][k]==-1) continue;
                    if (k + weight <= weight_capacity) 
                    {
                        memo[level_id + 1][k + weight] = max(memo[level_id + 1][k + weight], memo[level_id][k] + value);
                        vec_max[k + weight] = max(vec_max[k + weight], memo[level_id + 1][k + weight]);
                        //cout << "update (" << level_id+1 << ", " << k+weight << ") to " << memo[level_id+1][k+weight] << endl;
                    }
                }                
            }
            else
            {
                // unlimited knapsack, forward update
                memo[level_id+1] = memo[level_id]; //copy to the next level
                for (long long k = 0; k <= weight_capacity; k++)
                {
                    if (memo[level_id+1][k]==-1) continue;
                    if (k + weight <= weight_capacity) 
                    {
                        memo[level_id +1 ][k + weight] = max(memo[level_id+1][k + weight], memo[level_id+1][k] + value);
                        vec_max[k + weight] = max(vec_max[k + weight], memo[level_id+1][k + weight]);
                        //cout << "update (" << level_id+1 << ", " << k+weight << ") to " << memo[level_id+1][k+weight] << endl;
                    }
                }                  
            }
        }
        // print(vec_max);
        // cout << "***" << endl;
        // for (long long m=0; m<=num_levels; m++) print(memo[m]);
        // cout << endl;
        vector<vector<long long> > tmp(num_levels + 1, vector<long long>(weight_capacity + 1, -1));
        tmp[0] = vec_max;
        memo = tmp;
    }
    long long max_value = -1;
    for (long long k=0; k <= weight_capacity; k++)
    {
        max_value = max(max_value, vec_max[k]);
    }
    return max_value;
}


/***************** Knapsack with 2-dimensional capacity ********************************/
/*
This function aims to find the max value for a knapsack with 2-dimensional capacity (time_limit and weight_capacity),
the input: vector<vector<long long> > items contains all the items in the format of below:
{ {item_1_weight, item_1_time, item_1_value, item_1_category}, {item_2_weight, item_2_time, item_2_value, item_2_category}}
if item_1_category==1, it is a 0/1 knapsack, if item_1_category==-1, it is an unlimited knapsack.
*/
long long knapsackwith_2d_capacity(vector<vector<long long> > items, long long time_limit, long long weight_capacity)
{
    vector<vector<long long> > memo(time_limit + 1, vector<long long>(weight_capacity + 1, -1));
    long long num_items = items.size();
    memo[0][0] = 0;
    for (long long i = 0; i < num_items; i++)
    {
        long long weight = items[i][0], time1 = items[i][1], value = items[i][2], category = items[i][3];
        if (category==1)
        {
            // 0/1 knapsack, backward update
            for (long long j = time_limit; j >= 0; j--)
            {
                for (long long k = weight_capacity; k >= 0; k--)
                {
                    if (j + time1 <= time_limit && k + weight <= weight_capacity && memo[j][k] >= 0)
                    {
                        memo[j + time1][k + weight] = max(memo[j][k] + value, memo[j + time1][k + weight]);
                    }
                }
            }
        }
        else // unlimited knapsack, forward update
        {
            // 0/1 knapsack, backward update
            for (long long j = 0; j <= time_limit; j++)
            {
                for (long long k = 0; k <= weight_capacity; k++)
                {
                    if (j + time1 <= time_limit && k + weight <= weight_capacity && memo[j][k ]>= 0)
                    {
                        memo[j + time1][k + weight] = max(memo[j][k] + value, memo[j + time1][k + weight]);
                    }
                }
            } 
        }
        
    }
    long long max_value = -1;
    for (long long j = 0; j <= time_limit; j++)
    {
        for (long long k = 0; k <= weight_capacity; k++) max_value = max(max_value, memo[j][k]);
    }
    return max_value;
}


/**************************************************************************************
***************** Game theory DP **************************************************
**************************************************************************************/
/*
problem:
######## Pick a number from either end one by one ##############
dmoij problem: A Game
Input: 
4
4 6 2 3
Output: 9
Explanation: A chooses 3, B chooses 4, A chooses 6, B chooses 2

Idea:
Step-1, define dp[i][j] as the max score you can get for the subsequence from index-i to index-j
Step-2: for a sequence from i to j, you have two choices: 1) choose element-i, 2) choose element j. 
If you choose element-i, you friend has two choices: 1a) choose element (i+1) or 1b) choose element j, 
If you choose element-j you friend has two choices: 2a) choose element (j-1) or 2b) choose element i.
So: dp[i][j] = max (case-1, case-2)
Case-1 = min(case 1a, case 1b), case-2 = min(case 2a, case 2b) 
because you friend takes the better one from case 2a and case 2b

time complexity O(N^2), space complexity O(N^2)
*/

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n;
    cin >> n;
    vector <int> vec1(n + 1);
    // vector of numbers
    for (int i = 1; i <= n; i++) cin >> vec1[i];
    // dp[i][j]: the max score that the first player can get from subsequence from i to j
    vector <vector <int> > memo(n + 1, vector <int>(n + 1));
    // diagonally initialize
    for (int i = 1; i <= n; i++) memo[i][i] = vec1[i];
    // dp transition
    for (int d = 1; d <= n; d++) // distance between row_id and col_id
    {
        // row_id: start_index
        for (int i = 1; i <= n - d; i++)
        {
            int j = i + d; // col_id: end_index
            // there are only 2 elements
            if (i + 1 == j) memo[i][j] = max(vec1[i], vec1[j]);
            // more than 2 elements
            else memo[i][j] = max(vec1[i] + min(memo[i + 2][j], memo[i + 1][j - 1]), vec1[j] + min(memo[i][j - 2], memo[i + 1][j - 1]));
        }
    }
    cout << memo[1][n] << "\n";
}


/**************************************************************************************
***************** Interval DP **************************************************
**************************************************************************************/
/*
problem:
######## Longest Palindromic Subsequence using diagonal update ##############
Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Idea:
1, Define state: dp[i][j]: the max length of palindrome in substring from i to j, 
2, State transition: if str1[i]==str1[j], then dp[i][j] = dp[i+1][j-1] + 2, 
    else dp[i][j] = max(dp[i+1][j], dp[i][j-1]), 
in plain words, if head==tail, dp of cutting head and tail + 1, 
else, find max from cutting head and cutting tail,

time complexity O(N^2), space complexity O(N^2)
*/
int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    string str1;
    cin >> str1;
    int n = str1.size();
    //dp[i][j]: the max length of palindrome in substring from i to j, 
    vector <vector <int> > memo(n + 1, vector <int>(n + 1));
    // diagonally initialize
    for (int x = 1; x <= n; x++)
    {
        memo[x][x] = 1;
    }
    // dp transition by diagonally update
    for (int d = 1; d <= n; d++) // distance between row_id and col_id
    {
        for (int start = 1; start <= n; start++)
        {
            int i = start, j = start + d; // i is row, j is col
            if (i>n || j>n) continue;
            // case-1: head==tail
            if (str1[i - 1] == str1[j - 1]) 
            {
                memo[i][j] = memo[i+1][j - 1] + 2;
            }
            // case-2: head != tail
            else memo[i][j] = max(memo[i + 1][j], memo[i][j-1]);
        }
    }
    cout << memo[1][n] << "\n";
}

/*
problem:
######## Minimum number of characters to be inserted to  make a string a palindrome ##############
%%%%%%%%%%%%% row-by-row update from bottom with flipping array to save space $$$$$$$$$$$$$$$
dmoij problem: IOI '00 P1 - Palindrome
Input: 
5
Ab3bd
Output: 2
Explanation: The output palindromic is "dAb3bAd".

Idea:
1, Define state: dp[i][j]: the max length of palindrome in substring from i to j, 
2, State transition: if str1[i]==str1[j], then dp[i][j] = dp[i+1][j-1], 
    else dp[i][j] = min(dp[i][j-1]+1, dp[i+1][j]+1), 
in plain words, if head==tail, dp of cutting head and tail, 
else, find min from appending char to matching head and inserting char to matching tail,

time complexity O(N^2), space complexity O(N) by doing row-by-row update from bottom with flipping arrays
*/
int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    int n, pre = 0, cur = 1;
    string str1;
    cin >> n >> str1;
    // memo[i][j]: the min number of chars to be inserted for substring from i to j
    // inital_value is the value to be put in memo[k][k] diagonally
    int inital_value = 0;
    vector <vector <int> > memo(2, vector <int>(n + 1, inital_value));

    // dp transition from last row to the first row
    for (int i = n-1; i >=1; i--) // from last row to the fist row
    {
        for (int j = i+1; j<=n; j++) // col
        {
            // case-1: if head==tail
            if (str1[i - 1] == str1[j - 1]) 
            {
                //memo[i][j] = memo[i+1][j-1]; // replacing i with cur, and i+1 with pre
                memo[cur][j] = memo[pre][j - 1];
            }
            // case-2: head != tail
            else 
            {
                //memo[i][j] = min(memo[i+1][j] + 1, memo[i][j-1] + 1);
                memo[cur][j] = min(memo[pre][j] + 1, memo[cur][j-1] + 1);
            }
        }
    // flip arrays after a row is completed
    swap(pre, cur);

    }
    // output the pre row, since it has been swapped
    cout << memo[pre][n] << "\n";
}



/*
problem:
######## O(N) DP transition ##############
dmoij problem: Educational DP Contest AtCoder N - Slimes
Input: 
4
10 20 30 40
Output: 190
Explanation: 
(10, 20, 30, 40) → (30, 30, 40): cost = 0 + (10+20)
(30, 30, 40) → (60, 40): cost = 30 + (30+30)=90
(60, 40) → (100): cost = 90 + (40+40) = 190

Idea:
1, Define state: dp[i][j]: the min-cost to combine the sub-array from index-i to index-j
2, State transition: if we set the segment-point at i, we have dp[i][j] = v1[i] + dp[i+1][j] + sum[i+1, j], 
if we set the segment-point at i+1, we have dp[i][j] = dp[i][i+1] + sum[i, i+1] + dp[i+2][j] + sum[i+2, j], …
there are (j-1) cases, dp[i][j] = min(case-1, … case (j-i))
Update dp matrix diagonally

time complexity O(N^3), space complexity O(N^2)
*/

int main()
{
    cin.tie(0); cout.tie(0); cin.sync_with_stdio(0);
    long long n;
    cin >> n;
    // psa
    vector <long long> vec1(n + 1), psa = {0};
    for (int i = 1; i <= n; i++)
    {
        cin >> vec1[i];
        psa.emplace_back(psa.back() + vec1[i]);
    }
    // define dp state: the min-cost to combine the sub-array from index-i to index-j
    vector <vector <long long> > memo(n + 1, vector <long long>(n + 1, 1e18));
    
    // diagonally initialize
    for (int i = 1; i <= n; i++)
    {
        memo[i][i] = 0;
    }
    // dp transition
    for (int d = 1; d <= n -1; d++) // distance between row_id and col_id
    {
        for (int i = 1; i <= n - d; i++) // row_id: start_point
        {
            int j = i + d; // col_id: end_point
            // O(n) transition
            for (int t = i; t < j; t++)
            {
                // t is the segment-point, left=memo[i][t], right = memo[t + 1][j]
                memo[i][j] = min(memo[i][t] + memo[t + 1][j] + psa[j] - psa[i - 1], memo[i][j]);
            }
        }
    }
    cout << memo[1][n] << "\n";
}




