/*
 * @lc app=leetcode.cn id=590 lang=cpp
 *
 * [590] N叉树的后序遍历
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
    vector<int> postorder(Node* root) {
        vector<int> a;
        helper(root, a);
        return a;
    }

    void helper(Node* root, vector<int>& a){
        if(!root){
            return;
        }

        for(auto& c : root->children){
            helper(c, a);
        }

        a.push_back(root->val);
    }
};
// @lc code=end

