/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;  // initialise

        for(int val : coins){
            for(int i = 1; i <= amount; ++i){
                if(val <= i){
                    dp[i] = min(dp[i - val] + 1, dp[i]);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
// @lc code=end

