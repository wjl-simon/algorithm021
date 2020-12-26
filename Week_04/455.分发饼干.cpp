/*
 * @lc app=leetcode.cn id=455 lang=cpp
 *
 * [455] 分发饼干
 */

// @lc code=start
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // sort the g and s
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int const LEN_G = g.size();
        int const LEN_S = s.size();
        int ans = 0;

        int j = 0;
        for(int i = 0; i < LEN_S && j < LEN_G; ++i){
            if(s[i] >= g[j]){
                ++ans;
                j++;
            }
        }
        return ans;
    }
};
// @lc code=end

