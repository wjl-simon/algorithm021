/*
 * @lc app=leetcode.cn id=91 lang=cpp
 *
 * [91] 解码方法
 */

// @lc code=start
class Solution {
public:
    int numDecodings(string s) {
        int const LEN = s.size();
        if(LEN == 0 || s[0] == '0'){
            return 0;
        }
        vector<int> dp(LEN + 1, 1);

        for(int i = 1; i < LEN; ++i){
            if(s[i] == '0'){
                if(s[i - 1] == '1' || s[i - 1] == '2'){
                    dp[i + 1] = dp[i - 1];
                }
                else{
                    return 0;
                }
            }
            else if(s[i - 1] == '1' || s[i - 1] == '2' && '1' <= s[i] && s[i] <= '6'){
                dp[i + 1] = dp[i] + dp[i - 1];
            }
            else{
                dp[i + 1] = dp[i];
            }
        }
        return dp[LEN];
    }
};
// @lc code=end

