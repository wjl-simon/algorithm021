/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int const LEN = nums.size();
        int dp_max = nums[0], dp_min = nums[0];
        int ans = dp_max;
        
        for(int i = 1; i < LEN; ++i){
            int temp1 = dp_max, temp2 = dp_min;
            dp_max = max( max(temp1 * nums[i], nums[i]), temp2 * nums[i] );
            dp_min = min( min(temp2 * nums[i], nums[i]), temp1 * nums[i] );
            ans = max(dp_max, ans);
        }
        return ans;
    }
};
// @lc code=end

