/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */

// @lc code=start
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int const LEN = nums.size();
        int reachableEnd = LEN - 1;
        for(int i = LEN - 1; i >= 0; --i){
            if(nums[i] + i >= reachableEnd){
                reachableEnd = i;
            }
        }
        return reachableEnd == 0;
    }
};
// @lc code=end

