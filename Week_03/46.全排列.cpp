/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */

// @lc code=start
class Solution {
    vector<vector<int>> ans;

    void helper(int cur, vector<int>& a){
        if(cur == a.size()){
            ans.push_back(a);
            return;
        }
        int const LEN = a.size();
        for(int i = cur; i < LEN; ++i){
            swap(a[i], a[cur]);
            helper(cur + 1, a);
            swap(a[i], a[cur]);
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        helper(0, nums);
        return ans;
    }
};
// @lc code=end

