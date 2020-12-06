/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        int const LEN = nums.size();

        for(int i = 0; i < LEN; i++){
            if(nums[i]){
                nums[j] = nums[i];
                if(i != j){
                    nums[i] = 0;
                }
                ++j;
            } 
        }
    }
};
// @lc code=end

