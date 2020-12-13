/*
 * @lc app=leetcode.cn id=264 lang=cpp
 *
 * [264] 丑数 II
 */

// @lc code=start
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<int64_t,vector<int64_t>,greater<int64_t>> pq;
        pq.push(1);
        int64_t ans;

        for(int i = 0; i < n; ++i){
            ans = pq.top();
            pq.pop();
            while(!pq.empty() && pq.top() == ans){
                pq.pop();
            }
            pq.push(ans * 2);
            pq.push(ans * 3);
            pq.push(ans * 5);
        }
        return ans;
    }
};
// @lc code=end

