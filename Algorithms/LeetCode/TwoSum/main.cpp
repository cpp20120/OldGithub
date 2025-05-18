class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int se = target - nums[i];
            if (mp.count(se)) {
                return {mp[se], i};
            }
            mp[nums[i]] = i;
        }
        return {}; 
    }
};
