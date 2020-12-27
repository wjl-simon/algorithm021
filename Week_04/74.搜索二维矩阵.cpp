/*
 * @lc app=leetcode.cn id=74 lang=cpp
 *
 * [74] 搜索二维矩阵
 */

// @lc code=start
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int const m = matrix.size();
        int const n = matrix[0].size();
        int left = 0, right = m * n - 1;

        while(left <= right){
            int mid = left + (right - left) / 2;
            // translate it into coordinates
            int x = mid / n, y = mid % n;
            if(matrix[x][y] == target){
                return true;
            }
            else if(matrix[x][y] < target){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
        return false;
    }
};
// @lc code=end

