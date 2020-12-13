/*
 * @lc app=leetcode.cn id=429 lang=cpp
 *
 * [429] N 叉树的层序遍历
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(!root){
            return {};
        }

        vector<vector<int>> ans;
        queue<Node*> q;
        q.push(root);

        while(!q.empty()){
            // travse nodes from the same level
            vector<int> curLv;
            int LEN = q.size();
            for(int i = 0; i < LEN; ++i){
                Node* x = q.front();
                q.pop();
                curLv.push_back(x->val);
                // x's children enqueue
                for(auto& c : x->children){
                    q.push(c);
                }
            }
            ans.push_back(curLv);
        }
        return ans;
    }
};
// @lc code=end

