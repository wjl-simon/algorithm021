/*
 * @lc app=leetcode.cn id=50 lang=cpp
 *
 * [50] Pow(x, n)
 */

// @lc code=start
class Solution {
    // assume n is nonnegative
    double helper(double x, int64_t n){
        if(n == 0){
            return 1.0;
        }

        double temp = helper(x, n >> 1);
        if(n % 2 == 1){
            // odd
            return temp * temp * x;
        }
        else{
            // even
            return temp * temp;
        }
    }

public:
    double myPow(double x, int n) {
        int64_t N = n;
        if(N < 0){
            return 1 / helper(x, -N);
        }
        return helper(x, N);
    }
};
// @lc code=end

