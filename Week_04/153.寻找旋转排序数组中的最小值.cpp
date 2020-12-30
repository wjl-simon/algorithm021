/*
 * @lc app=leetcode.cn id=153 lang=cpp
 *
 * [153] 寻找旋转排序数组中的最小值
 */

// @lc code=start
class Solution {
public:
    int findMin(vector<int>& nums) {
        int const LEN = nums.size();
        int left = 0, right = LEN - 1;
        if(nums[0] <= nums[right]){
            return nums[0];
        }
        
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(mid + 1 < LEN && nums[mid] > nums[mid + 1]){
                return nums[mid + 1];
            }
            
            if(mid - 1 >= 0 && nums[mid - 1] > nums[mid]){
                return nums[mid];
            }

            if(nums[0] < nums[mid]){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }
        return -1;
    }
};
// @lc code=end

