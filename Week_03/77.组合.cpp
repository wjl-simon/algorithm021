/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 */

// @lc code=start
class Solution {
    vector<int> temp;
    vector<vector<int>> ans;

    // get the combinations of k numbers from cur to n
    void helper(int cur, int n, int k){
        if(k == 0){
            ans.push_back(temp);
            return;
        }
        // from cur to n: take another k numbers
        for(int i = cur; i <= n - (k - 1); ++i){
            // take nuber i in temp
            temp.push_back(i);
            // need another combinations of k-1 numbers (from cur + 1 to n) 
            helper(i + 1, n, k - 1);
            // undo the taking of number i in temp
            temp.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        helper(1, n, k);
        return ans;
    }
};
// @lc code=end

