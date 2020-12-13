/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> h;    // hash map

        int const LEN = strs.size();
        for(int i = 0; i < LEN; ++i){
            auto key = strs[i];
            // sort the string
            sort(key.begin(), key.end());
            // sorted string as the key, unsorted str as val
            h[key].push_back(strs[i]);
        }
        
        for(auto record: h){
            // put the unsorted strs as a group
            ans.push_back(record.second);
        }
        return ans;
    }
};
// @lc code=end

