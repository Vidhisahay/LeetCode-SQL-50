#include <vector>
#include <string>
#include <algorithm>
#include <utility> // for std::pair

class Solution {
private:
    // Helper function to count zeros and ones in a string
    // Returns a pair: {zeros, ones}
    std::pair<int, int> countZerosAndOnes(const std::string& str) {
        int zeros = 0;
        int ones = 0;
        for (char c : str) {
            if (c == '0') {
                zeros++;
            } else {
                ones++;
            }
        }
        return {zeros, ones};
    }

public:
    int findMaxForm(std::vector<std::string>& strs, int m, int n) {
        // Use a 2D vector for the DP table: dp[j][k]
        // dp[j][k] stores the max number of strings that can be formed
        // using exactly 'j' zeros and exactly 'k' ones.
        // Initialize all values to 0.
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        // Iterate through each string (item)
        for (const std::string& str : strs) {
            auto [zeros, ones] = countZerosAndOnes(str);

            // Standard Knapsack logic: Iterate backwards to prevent using the
            // same string multiple times in the current calculation.
            for (int j = m; j >= zeros; --j) { // Iterate through available zeros
                for (int k = n; k >= ones; --k) { // Iterate through available ones
                    
                    // The transition:
                    // dp[j][k] = max(
                    //   dp[j][k], // Option 1: Don't include the current string
                    //   dp[j - zeros][k - ones] + 1 // Option 2: Include the current string
                    // );
                    
                    dp[j][k] = std::max(dp[j][k], dp[j - zeros][k - ones] + 1);
                }
            }
        }

        // The result is the value in the cell corresponding to the full limits (m zeros, n ones)
        return dp[m][n];
    }
};