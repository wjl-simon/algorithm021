/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution {
private:
    vector<string> ans;

public:
    /**
     * @para left: # of used left brackets
     * @para right: # of used right brackets
     * @para n: quota for left or right brackets
     * @para s: current bracket pattern
    */
    void generate(int left, int right, int n, string s){
        // terminator
        if(left == n && right == n){
            ans.push_back(s);
            return;
        }
        
        // append a '(' as long as there's qouta left
        if(left < n){
            generate(left + 1, right, n, s + "(");
        }
        // append a right bracket if there're more left brackets
        if(left > right){
            generate(left, right + 1, n, s + ")");
        }
    }

    vector<string> generateParenthesis(int n) {
        generate(0, 0, n, "");
        return ans;
    }
};
// @lc code=end

