/*
 * @lc app=leetcode.cn id=515 lang=cpp
 *
 * [515] 在每个树行中找最大值
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if(!root){
            return {};
        }
        queue<TreeNode*> q;
        q.push(root);
        vector<int> res;
        int level = 0;

        while(!q.empty()){
            if(level + 1 > res.size()){
                res.push_back(INT_MIN);
            }

            int const LEN = q.size();
            for(int i = 0; i < LEN; ++i){
                TreeNode* x = q.front();
                q.pop();
                res[level] = max(res[level], x->val);
                if(x->left){
                    q.push(x->left);
                }
                if(x->right){
                    q.push(x->right);
                }
            }
            ++level;
        }
        return res;
    }
};
// @lc code=end

