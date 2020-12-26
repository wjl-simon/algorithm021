/*
 * @lc app=leetcode.cn id=433 lang=cpp
 *
 * [433] 最小基因变化
 */

// @lc code=start
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        // acceralate the searching
        unordered_set<string> lib(bank.begin(), bank.end());
        // dna bases
        vector<char> base = {'A', 'C', 'G', 'T'};

        queue<string> q; 
        q.push(start);
        unordered_set<string> vis;
        vis.insert(start);
        int ans = 0; 

        while(!q.empty()){
            int const LEN = q.size();
            for(int k = 0; k < LEN; ++k){
                string cur = q.front();
                q.pop();
                // check if we hit the ans
                if(!cur.compare(end)){
                    return ans;
                }
                // generate mulations on one bit
                for(int i = 0; i < 8; ++i){
                    string candidate = cur;
                    for(char ch : base){
                        if(candidate[i] == ch){
                            continue;
                        }
                        char backup = candidate[i];
                        candidate[i] = ch;
                        // if not valid mutation or have seen: prune
                        // unoredred_set::count(sth): is to test if there exsits sth
                        // unordered_set::emplace(sth): try to push sth and return a pair<>:
                        // its returned's second indicates if insertion sucessful
                        if(!lib.count(candidate) || !vis.emplace(candidate).second){
                            continue;
                        }
                        q.push(candidate);
                        candidate[i] = backup;  // restore: we only modify one bit
                    }
                }
            }
            // the same level: only one modification
            ++ans;
        }
        // no answer if reach here
        return -1;
    }
};
// @lc code=end

