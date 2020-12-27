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
        unordered_set<string> head({beginWord}), tail({endWord});
        unordered_set<string>* smaller = &head, *bigger = &tail;

        if(!dict.count(endWord)){
            return 0;
        }

        char letters[26];
        for(int i = 0; i < 26; ++i){
            letters[i] = i + 'a';
        }

        int ans = 2;

        while(!head.empty() && !tail.empty()){
            if(head.size() < tail.size()){
                smaller = &head;
                bigger = &tail;
            }
            else{
                smaller = &tail;
                bigger = &head;
            }
            unordered_set<string> reachable;
            for(auto it = smaller->begin(); it != smaller->end(); ++it){
                string word = *it;
                int const LEN = word.size();

                for(int i = 0; i < LEN; ++i){
                    char t = word[i];
                    for(char ch : letters){
                        word[i] = ch;
                        if(bigger->count(word)){
                            return ans;
                        }

                        if(dict.count(word)){
                            reachable.insert(word);
                            dict.erase(word);
                        }
                    }
                    word[i] = t;
                }
            }
            ++ans;
            smaller->swap(reachable);
        }
        return 0;
    }
};
// @lc code=end

