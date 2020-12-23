/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 */

// @lc code=start
class Solution {
    void helper(vector<vector<char>>& grid, int x, int y){
        int const m = grid.size();
        int const n = grid[0].size();
        if(x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '0'){
            return;
        }
        grid[x][y] = '0';
        // eliminate surrounding the 1's
        helper(grid, x + 1, y);
        helper(grid, x - 1, y);
        helper(grid, x, y + 1);
        helper(grid, x, y - 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int const m = grid.size();
        int const n = grid[0].size();
        int ans  = 0; // number of islands;

        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == '1'){
                    // eliminate the connected '1's
                    helper(grid, i, j);
                    ++ans;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

