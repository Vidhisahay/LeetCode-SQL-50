/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> numsSet(nums.begin(), nums.end());
        ListNode* dummyNode = new ListNode(0, head);
      
        for (ListNode* prevNode = dummyNode; prevNode->next != nullptr;) {
            if (numsSet.count(prevNode->next->val)) {
                prevNode->next = prevNode->next->next;
            } else {
                prevNode = prevNode->next;
            }
        }
      
        return dummyNode->next;
    }
};