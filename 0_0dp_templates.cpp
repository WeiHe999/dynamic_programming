/**************************************************************************************
***************** Knapsack Problems **************************************************
**************************************************************************************/


/***************** Generic Knapsack **********************************/
/*
This function converts items with limited amount to 0/1 items, form example, item_1 has weight 4, value 5, can
be used 3 times, denoted as {4, 5, 3}, can be converted to 2 0/1 items {{4, 5, 1}, {4*2, 5*2, 2}}
the output is stored in vector<vector<int> > new_items
*/
vector<vector<int> > new_items = {};
void convert_knapsack_items(vector<vector<int> > items, vector<vector<int> > new_items)
{
    new_items = {};
    for (int i = 0; i < items.size(); i++)
    {
        vector<int> cur_item = items[i];
        int amount = cur_item[2], weight = cur_item[0], value = cur_item[1], power = 0;
        if (amount < 2) 
        {
            new_items.push_back(cur_item);
            continue;
        }
        while (amount > 0)
        {
            int split_amount = pow(2, power);
            new_items.push_back({weight * min(split_amount, amount), value * min(split_amount, amount), 1});
            amount -= split_amount;
            power++;
        }
    }    
}


/* each knapsack has capacity of weight_capacity
each item has n levels, each level can be done at most 1 time (category=1) or unlimited times (category=-1)
items are put into a vector as below:
items ={ {item_1_weight, item_1_value, item_1_categoty}, {item_2_weight, item_2_value, item_2_categoty}} 
category: 1 is 0/1 knapsack, -1 is unlimited knapsack
 */
int knapsack(vector<vector<int> > items, int num_items, int weight_capacity)
{
    vector<int> memo(weight_capacity + 1, -1);
    memo[0] = 0;
    // update
    for (int i = 0; i < num_items; i++)
    {
        int weight = items[i][0], value = items[i][1], category = items[i][2];
        if (category==1)
        {
            // 0/1 knapsack, backward update
            for (int k = weight_capacity; k >= 0; k--)
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
            for (int k = 0; k <= weight_capacity; k++)
            {
                if (memo[k]==-1) continue;
                if (k + weight <= weight_capacity) 
                {
                    memo[k + weight] = max(memo[k + weight], memo[k] + value);
                }
            }                  
        }
    }
    int max_value = -1;
    for (int k=0; k <= weight_capacity; k++)
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

int conditional_knapsack(vector<vector<int> > items, int num_items, int num_levels, int weight_capacity)
{
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
            if (category==1)
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
