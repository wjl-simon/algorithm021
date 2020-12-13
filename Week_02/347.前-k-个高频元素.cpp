/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */

// @lc code=start
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int const LEN = nums.size();
        // pq: stored at vector<pair<int,int>>, using greater< pair<int, int> > to compare
        // pair: only compares the first 
        priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>> > pq;
        unordered_map<int, int> h;  // hash map
        vector<int> ans;

        // traverse the array to get stats
        for(int i = 0; i < LEN; ++i){
            h[nums[i]]++;
        }
        // populate the pq
        for(auto& record : h){
            // record: (num, freq)
            // a node in pq: pair(freq, num)
            pq.push({record.second, record.first});
            // keep the size == k
            while(pq.size() > k){
                pq.pop();
            }
        }
        // populate the ans
        while(!pq.empty()){
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
    }
};
// @lc code=end

