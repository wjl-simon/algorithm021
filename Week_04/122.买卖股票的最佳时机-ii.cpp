/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int const LEN = prices.size();
        for(int i = 0; i < LEN - 1; ++i){
            if(i < LEN - 1 && prices[i] < prices[i + 1]){
                // 可以当天买入当天卖出
                profit += prices[i + 1] - prices[i];
            }
        }
        return profit;
    }
};
// @lc code=end

