/*
 * @lc app=leetcode.cn id=316 lang=cpp
 *
 * [316] 去除重复字母
 */

// @lc code=start
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);
        vector<bool> visited(26, false);    // indicate if there exsits and is only one c in stack
        for(char c : s){
            ++count[c - 'a'];   // indicates the freq of c in s
        }

        string st;
        for(char c : s){
            // if c is not in the stack
            if(!visited[c - 'a']){
                while(!st.empty() && st.back() > c){
                    if(count[st.back() - 'a'] >= 1){
                        // pop off the top
                        visited[st.back() - 'a'] = false;   // remember, all letters are distinct
                        st.pop_back();
                    }
                    else{
                        break;
                    }
                }
                visited[c - 'a'] = true;
                st.push_back(c);
            }
            // c is in the stack: don't put it into stack again
            --count[c - 'a'];
        }

        return st;
    }
};
// @lc code=end

