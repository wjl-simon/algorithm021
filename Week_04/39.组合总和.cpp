/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */

// @lc code=start
class Solution {
    vector<int> temp;
    vector<vector<int>> ans;

    // target: the quantity we further need
    void backtracking(int cur, vector<int>& arr, int target){
        int const LEN = arr.size();
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        
        for(int i = cur; i < LEN; ++i){
            if(target - arr[i] < 0){
                break;
            }
            temp.push_back(arr[i]);
            backtracking(i, arr, target - arr[i]);
            temp.pop_back();
        }

    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(0, candidates, target);
        return ans;
    }
};
// @lc code=end

