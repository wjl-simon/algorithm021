# Week 3 Leetcode Additional/Good Snippets


## 78. 子集

### 版本一 回溯

帖子内容很多然而很精彩，这里仅贴上[传送门](https://leetcode-cn.com/problems/subsets/solution/c-zong-jie-liao-hui-su-wen-ti-lei-xing-dai-ni-gao-/)。

同时发现了一个很棒的博客[labuladong的算法小抄](https://labuladong.gitbook.io/algo/)

---

## 98. 验证二叉搜索树

### 版本一：验证其中序遍历序列（迭代）

BST的中序遍历是递增的（假设左子树严格小于```root->val```且右子树严格大于```root->val```），且此为充要条件，因此我们可以通过验证中序遍历序列是否递增来判定是否为BST。

```C++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stack;
        long long inorder = (long long)INT_MIN - 1;

        while (!stack.empty() || root != nullptr) {
            while (root != nullptr) {
                stack.push(root);
                root = root -> left;
            }
            root = stack.top();
            stack.pop();
            // 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
            if (root -> val <= inorder) {
                return false;
            }
            inorder = root -> val;
            root = root -> right;
        }
        return true;
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/validate-binary-search-tree/solution/yan-zheng-er-cha-sou-suo-shu-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二: 验证其中序遍历序列（递归）
该版本用中序递归遍历树判断是否为递增序列。这里用了一个叫```pre```的成员变量，用于储存上个一中序遍历序列元素。下面给出Java实现。

当然，可以设计一个函数签名为```function(TreeNode root, long pre)```的helper，然后```isValidBST()```调用之，这样就不用引入成员变量了。

```Java
class Solution {
    long pre = Long.MIN_VALUE;
    public boolean isValidBST(TreeNode root) {
        if (root == null) {
            return true;
        }
        // 访问左子树
        if (!isValidBST(root.left)) {
            return false;
        }
        // 访问当前节点：如果当前节点小于等于中序遍历的前一个节点，说明不满足BST，返回 false；否则继续遍历。
        if (root.val <= pre) {
            return false;
        }
        pre = root.val;
        // 访问右子树
        return isValidBST(root.right);
    }
}

作者：sweetiee
链接：https://leetcode-cn.com/problems/validate-binary-search-tree/solution/zhong-xu-bian-li-qing-song-na-xia-bi-xu-miao-dong-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 104. 二叉树的最大深度

### 版本一： 基于BFS

只要每到达一层，就```++res```，反正同层节点深度一致。只要某层有节点，总能到达该层而且在该层结束循环。

```C++
int maxDepth(TreeNode *root)
{
    if(root == NULL)
        return 0;
    
    int res = 0;
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty())
    {
        ++ res;
        for(int i = 0, n = q.size(); i < n; ++ i)
        {
            TreeNode *p = q.front();
            q.pop();
            
            if(p -> left != NULL)
                q.push(p -> left);
            if(p -> right != NULL)
                q.push(p -> right);
        }
    }
    
    return res;
}
```

---

## 111. 二叉树最小深度

## 版本一：基于BFS
本解法实际为本人独立解出,灵感源自**429. N 叉树的层序遍历**。比官方题解的基于BFS的应该复杂度要小。利用的性质是：当我们找到一个叶子节点时，直接返回这个叶子节点的深度。广度优先搜索的性质保证了最先搜索到的叶子节点的深度一定最小。

```C++
int minDepth(TreeNode* root) {
    if(!root){
        return 0;
    }

    queue<TreeNode*> q;
    q.push(root);
    int ans = 0;

    while(!q.empty()){
        int const LEN = q.size();
        ++ans;
        for(int i = 0; i < LEN; ++i){
            TreeNode* x = q.front();
            q.pop();
            if(!(x->left) && !(x->right)){
                return ans;
            }
            
            if(x->left){
                q.push(x->left);
            }
            if(x->right){
                q.push(x->right);
            }
        }
    }
    return ans;
}
```

---

## 剑指 Offer 06. 从尾到头打印链表

### 版本一： 递归回溯
这里用递归实现翻转储存链表：先递归调用```recur(head.next)```往下，直到回溯时自然会触发```tmp.add()```，把链表从尾到头保存到私有的tmp数组里。

实际上如果```reversePrint()```直接返回```tmp```可省去了数组复制。

```Java
class Solution {
    ArrayList<Integer> tmp = new ArrayList<Integer>();
    public int[] reversePrint(ListNode head) {
        recur(head);
        int[] res = new int[tmp.size()];
        for(int i = 0; i < res.length; i++)
            res[i] = tmp.get(i);
        return res;
    }
    void recur(ListNode head) {
        if(head == null) return;
        recur(head.next);
        tmp.add(head.val);
    }
}

作者：jyd
链接：https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/solution/mian-shi-ti-06-cong-wei-dao-tou-da-yin-lian-biao-d/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
### 版本二：栈
没什么好说，LIFO。只是应该要养成意识：倒序之类的应该要想起stack。

```Java
public int[] reversePrint(ListNode head) {
    LinkedList<Integer> stack = new LinkedList<Integer>();
    while(head != null) {
        stack.addLast(head.val);
        head = head.next;
    }

    int[] res = new int[stack.size()];
    for(int i = 0; i < res.length; i++)
        res[i] = stack.removeLast();

    return res;
}

作者：jyd
链接：https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/solution/mian-shi-ti-06-cong-wei-dao-tou-da-yin-lian-biao-d/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 226. 翻转二叉树

### 版本一：栈迭代（边DFS边交换子树）
本解法就是边交换子树边坐DFS：先按原来左右次序入栈，再交换左右子树，妙啊。

```C++
TreeNode* invertTree(TreeNode* root) {
    std::stack<TreeNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        TreeNode* p = stk.top();
        stk.pop();
        if (p) {
            stk.push(p->left);
            stk.push(p->right);
            std::swap(p->left, p->right);
        }
    }
    return root;
}
```

### 版本二：基于BFS的迭代
本解法也是边BFS边交换子树。虽然这里是先按照原来的左右顺序入栈，再交换左右子树。

```C++
TreeNode* invertTree(TreeNode* root) {
    
    if(nullptr == root) return root;
    
    queue<TreeNode*> myQueue;   // our queue to do BFS
    myQueue.push(root);         // push very first item - root

    while(!myQueue.empty()){    // run until there are nodes in the queue 
        
        TreeNode *node = myQueue.front();  // get element from queue
        myQueue.pop();                     // remove element from queue
                 
        if(node->left != nullptr){         // add left kid to the queue if it exists
            myQueue.push(node->left);
        }
        
        if(node->right != nullptr){        // add right kid 
            myQueue.push(node->right);
        }
        
        // invert left and right pointers      
        TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;

    }

    return root;
}
```

---

## 297. 二叉树的序列化与反序列化

### 版本一：基于DFS的递归

此DFS实质上为树的递归遍历（可先序、可中序、可后序）。serialize是如此，deserialize也是如此。

此解答来自国际站光头哥, 光头哥选用递归版先序遍历为框架，用空格作为分隔符，因而可以利用了```stringstream```方便地处理字符串的解析。此解法易懂、优雅。

学习学习使用```istringstream```和```ostringstream```。

```C++
class Solution {
public:
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:
    // NB：white sapce as the seperater
    void serialize(TreeNode* root, ostringstream& out) {
        // empty tree: is #
        if(!root){
            out << "# ";
        }
        out << root->val << ' ';
        serialize(root->left, out);
        serialize(root->right, out);
    }

    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;  // now val has be seperated from the string stream
        if (val == "#") // N.B. no white space after the #
            return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
```

---

## 236. 二叉树的最近公共祖先

### 版本一： 后序遍历 DFS 

**最近公共祖先的定义**： 
> 设节点 ```root``` 为节点 ```p```,```q``` 的某公共祖先，若其左子节点 ```root.left``` 和右子节点 ```root.right``` 都不是 ```p```,```q``` 的公共祖先，则称 ```root``` 是 “最近的公共祖先” 。

根据以上定义，若 ```root``` 是 ```p```,```q``` 的 最近公共祖先 ，则只可能为以下情况之一：

1. pp 和 qq 在 ```root``` 的子树中，且分列 ```root``` 的异侧（即分别在左、右子树中）；
2.  ```p == root``` ，且 ```q``` 在 ```root``` 的左或右子树中；
3. ```q == root``` ，且 ```p``` 在 ```root``` 的左或右子树中；

该版本通过递归对二叉树进行**后序遍历**。当遇到节点 ```p``` 或 ```q``` 时返回。从底至顶回溯，当节点 ```p```, ```q``` 在节点 ```root``` 的异侧时，节点 ```root``` 即为最近公共祖先，则向上返回 ```root``` 。

***终止条件：***
* 当越过叶节点，则直接返回 ```null``` ；
* 当 ```root``` 等于 ```p```或者等于```q``` ，则直接返回 ```root``` ；

***递推工作：***
* 开启递归左子节点，返回值记为 ```left``` ；
* 开启递归右子节点，返回值记为 ```right``` ；

***返回值：*** 根据 ```left``` 和 ```right``` ，可展开为四种情况；
1. 当 ```left``` 和 ```right``` 同时为空 ：说明 ```root``` 的左 / 右子树中都不包含 ```p```,```q``` ，返回 ```null``` ；
2. 当 ```left``` 和 ```right``` 同时不为空 ：说明 ```p```, ```q``` 分列在 ```root``` 的 异侧 （分别在 左 / 右子树），因此 ```root``` 为最近公共祖先，返回 ```root``` ；
3. 当 ```left``` 为空 ```right``` 不为空 ：```p```,```q``` 都不在 ```root``` 的左子树中，直接返回 ```right``` 。具体可分为两种情况：
    * ```p```, ```q```其中一个在 ```root``` 的 右子树 中，此时 ```right == p``` 或者 ```right == q```
    * ```p```, ```q``` 两节点都在 ```root``` 的 右子树 中，此时的 ```right``` 指向 最近公共祖先节点 ；
4. 当 ```left``` 不为空 ， ```right``` 为空 ：与情况 3. 同理；

各个情况的展开写法如下：
```Java
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if(root == null || root == p || root == q) return root;

        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);

        if(left == null && right == null) return null; // 1.
        if(left == null) return right; // 3.
        if(right == null) return left; // 4.
        return root; // 2. if(left != null and right != null)
    }
}ava
```

下面是优化后写法：
```Java
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if(root == null || root == p || root == q) return root;
        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);
        if(left == null) return right;
        if(right == null) return left;
        return root;
    }
}

作者：jyd
链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```