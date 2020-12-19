/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
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
private:
    unordered_map<int, int> map;
    /**
     * [pLeft, pRight]: preorder sequence
     * [iLeft, iRight]: inorder sequence
     */
    TreeNode* helper(vector<int>& pre, vector<int>& in, int pLeft, int pRight, int iLeft, int iRight){
        if(pLeft > pRight){
            return nullptr;
        }
        // pLeft points to the root at preorder
        // the in seq index of the root
        int iRoot = map[pre[pLeft]];

        // size of the left subtree
        int sizeL = iRoot - iLeft;

        // root node
        TreeNode* root = new TreeNode(pre[pLeft]);
        // build its left and right subtree
        root->left = helper(pre, in, pLeft + 1, pLeft + sizeL, iLeft, iRoot - 1);
        root->right = helper(pre, in, pLeft + sizeL + 1, pRight, iRoot + 1, iRight);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // build a hash map for the entire inorder sequence
        int const LEN = inorder.size();
        for(int i = 0; i < LEN; ++i){
            map[inorder[i]] = i;
        }
        return helper(preorder, inorder, 0, LEN - 1, 0, LEN - 1);
    }
};
// @lc code=end

