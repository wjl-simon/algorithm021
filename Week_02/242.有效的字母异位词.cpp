/*
 * @lc app=leetcode.cn id=242 lang=cpp
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()){
            return false;
        }

        int const LEN = s.size();
        int* count = new int[26]();

        for(int i = 0; i < LEN; ++i){
            ++count[s[i] - 'a'];
            --count[t[i] - 'a'];
        }
        
        for(int i = 0; i < 26; ++i){
            if(count[i] != 0){
                delete[] count;
                return false;
            }
        }
        delete[] count;
        return true;
    }
};
// @lc code=end

