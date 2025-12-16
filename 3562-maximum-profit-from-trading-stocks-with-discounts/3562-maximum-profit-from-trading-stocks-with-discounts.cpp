#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<int> present, future;
    int budget;
   
    vector<int> memo[1005][2];
    bool visited[1005][2];
    void merge(vector<int>& dp_acc, const vector<int>& dp_child) {
        // Create a temp copy to store new max values
        vector<int> next_dp = dp_acc;
        for (int w = budget; w >= 0; --w) {
            for (int k = 0; k <= w; ++k) {
                // If both parts are valid states
                if (dp_acc[w - k] > -1e9 && dp_child[k] > -1e9) {
                    next_dp[w] = max(next_dp[w], dp_acc[w - k] + dp_child[k]);
                }
            }
        }
        dp_acc = next_dp;
    }

public:
    // Helper function to solve Tree DP
    vector<int> dfs(int u, bool parent_bought) {
        if (visited[u][parent_bought]) {
            return memo[u][parent_bought];
        }

        vector<int> res_skip(budget + 1, -1e9); // -1e9 represents impossible/invalid
        res_skip[0] = 0;

        for (int v : adj[u]) {
            vector<int> child_res = dfs(v, false);
            merge(res_skip, child_res);
        }

      
        int cost = parent_bought ? present[u - 1] / 2 : present[u - 1];
        int profit = future[u - 1] - cost;

        vector<int> res_buy(budget + 1, -1e9);
        
        // Only proceed if we can afford U alone (initially)
        if (cost <= budget) {
            res_buy[cost] = profit; // Initial state with just U            
            vector<int> children_sum(budget + 1, -1e9);
            children_sum[0] = 0;
            
            for (int v : adj[u]) {
                vector<int> child_res = dfs(v, true);
                merge(children_sum, child_res);
            }

           
            fill(res_buy.begin(), res_buy.end(), -1e9);
            
            for (int w = 0; w <= budget - cost; ++w) {
                if (children_sum[w] > -1e9) {
                    res_buy[w + cost] = max(res_buy[w + cost], children_sum[w] + profit);
                }
            }
        }

                vector<int> final_res(budget + 1);
        for (int w = 0; w <= budget; ++w) {
            final_res[w] = max(res_skip[w], res_buy[w]);
        }

        visited[u][parent_bought] = true;
        memo[u][parent_bought] = final_res;
        return final_res;
    }

    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        this->present = present;
        this->future = future;
        this->budget = budget;
        
        // Build Tree
        adj.assign(n + 1, vector<int>());
        for (auto& edge : hierarchy) {
            adj[edge[0]].push_back(edge[1]);
        }
        
        // Reset DP
        for(int i=0; i<=n; ++i) {
            visited[i][0] = visited[i][1] = false;
        }

        // The CEO (node 1) has no boss, so parent_bought is effectively false
        vector<int> result = dfs(1, false);

        // Return the best profit possible within the budget
        int max_p = 0;
        for (int p : result) {
            max_p = max(max_p, p);
        }
        return max_p;
    }
};