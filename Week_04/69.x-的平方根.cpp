/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根
 */

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        int64_t left = 0, right = x;

        while(left <= right){
            int64_t mid = left + (right - left) / 2;
            if(mid * mid <= x){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
        return right;
    }
};
// @lc code=end

