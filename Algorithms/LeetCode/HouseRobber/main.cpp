class Solution {
public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        if (n==1) return nums[0];
        vector<int> p(2, 0);
        p[1]=nums[0];
        for(int i=1; i<n; i++){
            p[(i+1)&1]=max(p[(i-1)&1]+nums[i], p[i&1]);
        }
        return p[n&1];
    }
};
