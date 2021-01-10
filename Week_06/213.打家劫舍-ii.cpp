/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

// @lc code=start
class Solution {
    int helper(vector<int>& nums, int lo, int hi){
        int const LEN = hi - lo + 1;
        if(LEN <= 0){
            return 0;
        }
        else if(LEN == 1){
            return nums[lo];
        }

        vector<int> dp(LEN, 0);
        dp[0] = nums[lo];
        dp[1] = max(nums[lo], nums[lo + 1]);

        for(int i = 2; i < LEN; ++i){
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i + lo]);
        }
        return dp[LEN - 1];
    }

public:
    int rob(vector<int>& nums) {
        int const LEN  = nums.size();
        if(LEN <= 0){
            return 0;
        }
        else if(LEN == 1){
            return nums[0];
        }

        // not rob house 0
        int ans1 = helper(nums, 1, LEN - 1);
        // may rob house 0
        int ans2 = helper(nums, 0, LEN - 2);
        
        return max(ans1, ans2); 
    }
};
// @lc code=end

