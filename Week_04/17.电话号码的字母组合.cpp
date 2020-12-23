/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start
class Solution {
    unordered_map<int, string> map;
    vector<string> ans;
    string comb;

    void helper(int digitIdx, string digits){
        if(digitIdx == digits.size()){
            ans.push_back(comb);
            return;
        }
        // the digit in int form
        int digit = digits[digitIdx] - '0';
        // the corresponding candidate letters to choose from
        string collection = map[digit];
        for(char ch : collection){
            // take ch as the digitIdx-th letter
            comb.push_back(ch);
            // recur
            helper(digitIdx + 1, digits);
            // undo
            comb.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()){
            return {};
        }

        map[2] = "abc";
        map[3] = "def";
        map[4] = "ghi";
        map[5] = "jkl";
        map[6] = "mno";
        map[7] = "pqrs";
        map[8] = "tuv";
        map[9] = "wxyz";
        helper(0, digits);
        return ans;
    }
};
// @lc code=end

