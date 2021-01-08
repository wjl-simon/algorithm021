/*
 * @lc app=leetcode.cn id=63 lang=cpp
 *
 * [63] 不同路径 II
 */

// @lc code=start
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int const m = obstacleGrid.size();
        int const n = obstacleGrid[0].size();
        vector<int> dp(n, 0);
        // initialise
        if(obstacleGrid[0][0] == 0){
            dp[0] = 1;
        }

        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(obstacleGrid[i][j] == 1){
                    // there's an obstacle
                    dp[j] = 0;
                }        
                else if(j > 0){
                    dp[j] += dp[j - 1];
                }
            }
        }
        return dp[n - 1];
    }
};// @lc code=end

