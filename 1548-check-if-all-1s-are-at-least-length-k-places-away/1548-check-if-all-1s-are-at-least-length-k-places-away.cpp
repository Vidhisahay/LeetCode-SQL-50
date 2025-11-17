class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int prevOneIndex = -(k + 1);
      
        // Iterate through each element in the array
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                if (i - prevOneIndex - 1 < k) {
                    return false;
                }
                prevOneIndex = i;
            }
        }
      
        // All pairs of 1's satisfy the distance requirement
        return true;
    }
};