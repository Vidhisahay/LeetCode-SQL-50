class Solution {
public:
    
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        // Store indices of valid coupons
        vector<int> validIndices;
      
        // Define set of valid business lines
        unordered_set<string> validBusinessLines = {
            "electronics", 
            "grocery", 
            "pharmacy", 
            "restaurant"
        };

        // Iterate through all coupons to find valid ones
        for (int i = 0; i < code.size(); ++i) {
            const string& couponCode = code[i];
            const string& business = businessLine[i];
            bool isActiveCoupon = isActive[i];
          
            
            if (isActiveCoupon && 
                validBusinessLines.count(business) && 
                isValidCouponFormat(couponCode)) {
                validIndices.push_back(i);
            }
        }

        // Sort valid coupon indices by business line (primary) and coupon code (secondary)
        sort(validIndices.begin(), validIndices.end(), [&](int indexA, int indexB) {
            // First compare by business line
            if (businessLine[indexA] != businessLine[indexB]) {
                return businessLine[indexA] < businessLine[indexB];
            }
            // If business lines are same, compare by coupon code
            return code[indexA] < code[indexB];
        });

        // Build result vector with sorted valid coupon codes
        vector<string> result;
        for (int index : validIndices) {
            result.push_back(code[index]);
        }
      
        return result;
    }

private:
    
    bool isValidCouponFormat(const string& couponCode) {
        // Empty strings are invalid
        if (couponCode.empty()) {
            return false;
        }
      
        // Check each character is alphanumeric or underscore
        for (char ch : couponCode) {
            if (!isalnum(ch) && ch != '_') {
                return false;
            }
        }
      
        return true;
    }
};