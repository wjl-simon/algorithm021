/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除排序数组中的重复项
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (!nums.size()){
            return 0;
        }

        int const LEN = nums.size();
        int i = 0;
        for (int j = 1; j < LEN; ++j) {
            if (nums[j] != nums[i]) {
                nums[++i] = nums[j];
            }
        }
        return ++i;
    }

};
// @lc code=end

