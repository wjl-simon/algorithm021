/*
 * @lc app=leetcode.cn id=40 lang=cpp
 *
 * [40] 组合总和 II
 */

// @lc code=start
class Solution {
    vector<int> temp;
    vector<vector<int>> ans;

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
            // 这里，必须是i > cur而非i > 0: 否则当i == cur，arr[cur]会和arr[cur - 1]比较！
            // 而本次循环我们不应该关心cur[cur - 1]!!!!!!
            if(i > cur && arr[i - 1] == arr[i]){
                continue;
            }
            temp.push_back(arr[i]);
            // 因为只可以选一次而非无限次，cur应当更新为i + 1而非i，更非cur
            backtracking(i + 1, arr, target - arr[i]);
            temp.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(0, candidates, target);
        return ans;
    }
};
// @lc code=end

