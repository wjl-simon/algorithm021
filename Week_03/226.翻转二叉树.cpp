/*
 * @lc app=leetcode.cn id=226 lang=cpp
 *
 * [226] 翻转二叉树
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root){
            return nullptr;
        }
        // swap the left/right subtree
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        
        // invert the subtree 
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
        return root;
    }
};
// @lc code=end

