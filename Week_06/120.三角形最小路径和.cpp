/*
 * @lc app=leetcode.cn id=120 lang=cpp
 *
 * [120] 三角形最小路径和
 */

// @lc code=start
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int const m = triangle.size();
        // from ((i), j) to the last row that has the least path sum
        vector<int> dp(triangle[m - 1].begin(), triangle[m - 1].end());

        for(int i = m - 2; i >= 0; --i){
            int const n = triangle[i].size();
            for(int j = 0; j < n; ++j){
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }
        return dp[0];
    }
};
// @lc code=end

