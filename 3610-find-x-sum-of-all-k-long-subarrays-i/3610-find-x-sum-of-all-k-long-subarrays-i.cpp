class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        using pii = pair<int, int>;  // pair of (frequency, value)
      
        // Two sets to maintain top x elements and remaining elements
        set<pii> topX;        // Stores the x most frequent elements
        set<pii> remaining;   // Stores elements not in top x
        int xSum = 0;         // Sum of (frequency * value) for top x elements
      
        // Frequency map to track count of each element
        unordered_map<int, int> frequency;
      
        // Lambda function to add an element to the appropriate set
        auto addElement = [&](int value) {
            if (frequency[value] == 0) {
                return;
            }
          
            pii element = {frequency[value], value};
          
            // If topX is empty or current element should be in topX
            if (!topX.empty() && element > *topX.begin()) {
                xSum += element.first * element.second;  // Add to sum
                topX.insert(element);
            } else {
                remaining.insert(element);
            }
        };
      
        // Lambda function to remove an element from its current set
        auto removeElement = [&](int value) {
            if (frequency[value] == 0) {
                return;
            }
          
            pii element = {frequency[value], value};
          
            // Try to find and remove from topX set
            auto it = topX.find(element);
            if (it != topX.end()) {
                xSum -= element.first * element.second;  // Subtract from sum
                topX.erase(it);
            } else {
                // Remove from remaining set
                remaining.erase(element);
            }
        };
      
        vector<int> result;
      
        // Sliding window approach
        for (int i = 0; i < nums.size(); ++i) {
            // Update frequency for current element
            removeElement(nums[i]);      // Remove old frequency entry
            ++frequency[nums[i]];         // Increment frequency
            addElement(nums[i]);          // Add with new frequency
          
            // Calculate window start index
            int windowStart = i - k + 1;
            if (windowStart < 0) {
                continue;  // Window not yet complete
            }
          
            // Balance the sets: move elements from remaining to topX if needed
            while (!remaining.empty() && topX.size() < x) {
                pii largestRemaining = *remaining.rbegin();
                xSum += largestRemaining.first * largestRemaining.second;
                remaining.erase(largestRemaining);
                topX.insert(largestRemaining);
            }
          
            // Balance the sets: move excess elements from topX to remaining
            while (topX.size() > x) {
                pii smallestTop = *topX.begin();
                xSum -= smallestTop.first * smallestTop.second;
                topX.erase(smallestTop);
                remaining.insert(smallestTop);
            }
          
            // Add current window's x-sum to result
            result.push_back(xSum);
          
            // Remove the element going out of window
            removeElement(nums[windowStart]);      // Remove old frequency entry
            --frequency[nums[windowStart]];        // Decrement frequency
            addElement(nums[windowStart]);          // Add with new frequency
        }
      
        return result;
    }
};