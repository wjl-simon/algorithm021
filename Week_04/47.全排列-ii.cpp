/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */

// @lc code=start
class Solution {
    vector<int> perm;
    vector<vector<int>> ans;
    vector<int> vis;

    void helper(int cur, vector<int>& a){
        if(cur == a.size()){
            ans.push_back(perm);
            return;
        }
        
        int const LEN = a.size();
        for(int i = 0; i < LEN; ++i){
            // if this char is filled or is duplicated with the previous: ignore
            if(vis[i] || i > 0 && a[i] == a[i - 1] && vis[i - 1]){
                continue;
            }
            // put a[i] at position cur into this permutation
            perm.push_back(a[i]);
            vis[i] = 1;
            // continue to put
            helper(cur + 1, a);
            // undo (backtrace)
            perm.pop_back();
            vis[i] = 0;
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // sort the array s.t. identical elements are adjacent
        sort(nums.begin(), nums.end());
        //
        vis.resize(nums.size());
        helper(0, nums);
        return ans;
    }
};
// @lc code=end

