/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        int water = 0;
        stack<int> st;
        int const LEN = height.size();

        for(int i = 0; i < LEN; ++i){
            while(!st.empty() && height[st.top()] < height[i]){
                int top = st.top();
                st.pop();
                if(st.empty()){
                    break;
                }
                int h = min(height[i], height[st.top()]) - height[top];
                water += (i - st.top() - 1) * h;
            }
            st.push(i);
        }
        return water;
    }
};
// @lc code=end

