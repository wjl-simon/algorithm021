/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int const LEN = prices.size();
        if(LEN < 1){
            return 0;
        }
        // dp[i]: max. possible profit by day i
        vector<int> dp(LEN, 0); // day 0: buying prohibited
        // min price
        int minPrice = prices[0];

        for(int i = 1; i < LEN; ++i){
            minPrice = min(minPrice, prices[i]);
            dp[i] = max(dp[i - 1], prices[i] - minPrice);
        }
        return dp[LEN - 1];
    }
};
// @lc code=end

