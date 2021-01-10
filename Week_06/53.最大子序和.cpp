/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子序和
 */

// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // the max subarr sum that ended at nums[i]
        // dp[i] is either: nums[i] itself, or just dp[i - 1] (without nums[i])
        int const LEN = nums.size();
        vector<int> dp(nums.begin(), nums.end());
        // the max among the dp is the ans
        int ans = dp[0];

        for(int i = 1; i < LEN; ++i){
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};
// @lc code=end

