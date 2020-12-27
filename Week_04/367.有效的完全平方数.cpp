/*
 * @lc app=leetcode.cn id=367 lang=cpp
 *
 * [367] 有效的完全平方数
 */

// @lc code=start
class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num < 2){
            return true;
        }
        int64_t left = 0, right = num / 2;

        while(left <= right){
            int64_t mid = left + (right - left) / 2;
            int64_t t = mid * mid;
            if(t == num){
                return true;
            }
            else if(t < num){
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

