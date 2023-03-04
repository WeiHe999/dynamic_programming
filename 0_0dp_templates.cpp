/**************************************************************************************
***************** Knapsack Problems **************************************************
**************************************************************************************/


/***************** Conditonal Knapsack **********************************/
/* each knapsack has capacity of weight_capacity
each item has n levels, each level can be done at most 1 time (category=0) or unlimited times (category=1)
items are put into a vector as below:
    items ={ {item_1_level_1_weight, item_1_level_1_value, item_1_level_1_categoty, 
    item_1_level_2_weight, item_1_level_2_value, item_1_level_2_categoty}, 
    {item_2_level_1_weight, item_2_level_1_value, item_2_level_1_categoty}} 
    category: 0 is 0/1 knapsack, 1 is unlimited pnapsack
 */

int conditional_knapsack(vector<vector<int> > items, int num_items, int num_levels, int weight_capacity)
{
    /*
    items ={ {item_1_level_1_weight, item_1_level_1_value, item_1_level_1_categoty, item_1_level_2_weight, item_1_level_2_value, item_1_level_2_categoty}, 
    {item_2_level_1_weight, item_2_level_1_value, item_2_level_1_categoty}} 
    category: 0 is 0/1 knapsack, 1 is unlimited pnapsack
    */
    vector<vector<int> > memo(num_levels + 1, vector<int>(weight_capacity + 1, -1));
    memo[0][0] = 0;
    // update
    vector<int> vec_max = memo[0];
    for (int i = 0; i < num_items; i++)
    {
        for (int j=0; j< items[i].size(); j+=3)
        {
            int level_id = j/3, weight = items[i][j], value = items[i][j+1], category = items[i][j+2];
            //cout << "weight=" << weight << ", value=" << value << ", category=" << category << endl;
            if (category==0)
            {
                // 0/1 knapsack, backward update
                for (int k = weight_capacity; k >= 0; k--)
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
                for (int k = 0; k <= weight_capacity; k++)
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
        // for (int m=0; m<=num_levels; m++) print(memo[m]);
        // cout << endl;
        vector<vector<int> > tmp(num_levels + 1, vector<int>(weight_capacity + 1, -1));
        tmp[0] = vec_max;
        memo = tmp;
    }
    int max_value = -1;
    for (int k=0; k <= weight_capacity; k++)
    {
        max_value = max(max_value, vec_max[k]);
    }
    return max_value;
}
