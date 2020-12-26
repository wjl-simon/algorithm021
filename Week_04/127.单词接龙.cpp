/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 */

// @lc code=start
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        unordered_set<string> vis({beginWord});
        queue<string> q; q.push(beginWord);
        // letters
        char letters[26];   
        for(int i = 0; i < 26; ++i){
            letters[i] = i + 'a';
        }
        // answer
        int ans = 1;

        while(!q.empty()){
            int const LEN = q.size();
            for(int i = 0; i < LEN; ++i){
                string cur = q.front();
                q.pop();
                if(!cur.compare(endWord)){
                    return ans;
                }
                // generate candidate words
                for(int j = 0; j < cur.size(); ++j){
                    string candidate = cur;
                    for(char const ch : letters){
                        if(ch == candidate[j]){
                            continue;
                        }
                        char backup = candidate[j];
                        candidate[j] = ch;
                        if(!dict.count(candidate)|| !vis.emplace(candidate).second){
                            candidate[j] = backup;
                            continue;
                        }
                        q.push(candidate);
                        candidate[j] = backup;
                    }
                }
            }
            ++ans;
        }
        return 0;
    }
};
// @lc code=end

