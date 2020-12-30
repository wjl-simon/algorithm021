/*
 * @lc app=leetcode.cn id=90 lang=cpp
 *
 * [90] 子集 II
 */

// @lc code=start
class Solution {
    vector<int> temp;
    vector<vector<int>> ans;

    void backtracking(int cur, vector<int>& a){
        // 此题非常特殊，所有路径都应该加入结果集，所以不存在结束条件。
        // 或者说当 start 参数越过数组边界的时候，程序就自己跳过下一层递归了，因此不需要手写结束条件,直接加入结果集
        ans.push_back(temp);
        int const LEN = a.size();
        for(int i = cur; i < LEN; ++i){
            if(i > cur && a[i - 1] == a[i]){
                continue;
            }
            temp.push_back(a[i]);
            backtracking(i + 1, a);
            temp.pop_back();
        }
    }
    

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(0, nums);
        return ans;
    }
};
// @lc code=end

