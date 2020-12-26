# Week 4 Leetcode Additional / Good Snippets

## 316. 去除重复字母

### 版本一：贪心 + 栈

本题有一个简单版 [402. 移掉 K 位数字](https://leetcode-cn.com/problems/remove-k-digits/), 配合[该回答题解传送门](https://leetcode-cn.com/problems/remove-duplicate-letters/solution/yi-zhao-chi-bian-li-kou-si-dao-ti-ma-ma-zai-ye-b-4/)。

其中，P402是在不断单调去重后截取剩余的的前```n - k```个数字即为答案；而本题因为每个字母都有一个```k```（即所谓的每个字母各自应该被应该去掉的个数），此举不可行；然而因为只要求字母只剩下一个，我们可以在遍历的时候简单地判断其是否在栈上即可。

```Python
class Solution:
    def removeDuplicateLetters(self, s) -> int:
        stack = []
        remain_counter = collections.Counter(s)

        for c in s:
            if c not in stack:
                while stack and c < stack[-1] and  remain_counter[stack[-1]] > 0:
                    stack.pop()
                stack.append(c)
            remain_counter[c] -= 1
        return ''.join(stack)

作者：fe-lucifer
链接：https://leetcode-cn.com/problems/remove-duplicate-letters/solution/yi-zhao-chi-bian-li-kou-si-dao-ti-ma-ma-zai-ye-b-4/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
至于C++代码即为[官方题解](https://leetcode-cn.com/problems/remove-duplicate-letters/solution/qu-chu-zhong-fu-zi-mu-by-leetcode-soluti-vuso/)，两者主要区别是在C++中做```if c not in stack:```的判断需要额外引入一个数组来实现。

---

# 47. 全排列 II

## 版本一

其实此题位46. 全排列（不含重复元素）的升级版。在此之前先提一下**46. 全排列**的一个更加通用的**一般解法**：

```C++
class Solution {
    vector<int> perm;
    vector<vector<int>> ans;
    vector<int> vis;

    void helper(int cur, vector<int>& a){
        if(cur == a.size()){
            ans.push_back(perm);
            return;
        }
        
        int const LEN = a.size();
        for(int i = 0; i < LEN; ++i){
            if(vis[i]){
                continue;
            }
            // put a[i] at position cur into this permutation
            perm.push_back(a[i]);
            vis[i] = 1;
            // continue to put
            helper(cur + 1, a);
            // undo (backtrace)
            perm.pop_back();
            vis[i] = 0;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vis.resize(nums.size());
        helper(0, nums);
        return ans;
    }
};
```

而本题是有重复元素的，比如 [1,2,2']，那么答案 [1,2,2'] 和 [1,2',2] 就其实是一样的，在保存结果的时候，我们只选择其一。

我们为了高效地找到重复元素，我们最好先提前对```nums```排序**使得重复元素们挨在一起**。然后，例如我们已经存了[1, 2, 2']后，再尝试填一个排列，填到[1, _, _],尝试第二个填2'，则我们应该要察觉到这是重复的，也即**剪枝**。我们如何减枝呢？ 在排好序之后，只需要在```for```中间的```if```加一个or的判断：
```C++
if (i > 0 && nums[i] == nums[i - 1] && vis[i - 1]) {
    continue;
}
```
也即：如果前一个数字已经写过，并且与当前数字相等那么我们应该跳过。
这样，当[1, _, _],尝试第二个填2'的时候就会自动跳过后面的步骤，因为肯定是不合法的。

---

## 200. 岛屿数量

### 版本一： BFS
核心思想依旧是把与刚找到的```'1'```相连的1们变成0，只不过这次的顺序是BFS：

> 为了求出岛屿的数量，我们可以扫描整个二维网格。如果一个位置为 11，则将其加入队列，开始进行广度优先搜索。在广度优先搜索的过程中，每个搜索到的 11 都会被重新标记为 00。直到队列为空，搜索结束。
>
>最终岛屿的数量就是我们进行广度优先搜索的次数。
>
>作者：LeetCode
>链接：https://leetcode-cn.com/problems/number-of-islands/solution/dao-yu-shu-liang-by-leetcode/
>来源：力扣（LeetCode）
>著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

代码如下：
```C++
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    // 找到一个1，记录数量，并且置0
                    ++num_islands;
                    grid[r][c] = '0';
                    queue<pair<int, int>> neighbors;    // 记录为1的坐标
                    neighbors.push({r, c});
                    // 开始把相邻的1们变为0
                    while (!neighbors.empty()) {
                        auto rc = neighbors.front();    // 取出一个坐标
                        neighbors.pop();
                        int row = rc.first, col = rc.second;
                        // 看上下左右有没有'1'，有则其坐标入queue
                        if (row - 1 >= 0 && grid[row-1][col] == '1') {
                            neighbors.push({row-1, col});
                            grid[row-1][col] = '0';
                        }
                        if (row + 1 < nr && grid[row+1][col] == '1') {
                            neighbors.push({row+1, col});
                            grid[row+1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col-1] == '1') {
                            neighbors.push({row, col-1});
                            grid[row][col-1] = '0';
                        }
                        if (col + 1 < nc && grid[row][col+1] == '1') {
                            neighbors.push({row, col+1});
                            grid[row][col+1] = '0';
                        }
                    }
                }
            }
        }

        return num_islands;
    }
};

作者：LeetCode
链接：https://leetcode-cn.com/problems/number-of-islands/solution/dao-yu-shu-liang-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 127. 单词接龙

### 版本一 双向广度优先搜索

**想法**:
> 如果使用两个同时进行的广搜可以有效地**减少搜索空间**。一边从 beginWord 开始，另一边从 endWord 开始。我们每次从两边各扩展一层节点，当发现某一时刻两边都访问过同一顶点时就停止搜索。这就是双向广度优先搜索，它可以可观地减少搜索空间大小，从而提高代码运行效率。

代码来自国际站，解释如下：
> This solution uses two pointers ```smallerSet``` and ```biggerSet``` to switch to the smaller set (the one with smaller size between the two search spaces) at each step to save time.

```C++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end()), head, tail, *smallerSet, *biggerSet;
        if (dict.find(endWord) == dict.end()) {
            return 0;
        }
        // head 和 tail 相当于queue，存放各自的搜索空间

        /*         
            Search from both ends.
                    
            From 'beginWord', find the set of words which are one character from 'beginWord'.
                    
            Do the same to 'endWord', form a set of words one character from 'endWord'.

            Check each word in the smaller of ('beginWord','endWord'), if it is in the other set.
            If it is, we are done.
            Otherwise, for each word in smaller('begigWord', 'endWord'), update the set (by changing one character)
        */
        head.insert(beginWord);
        tail.insert(endWord);
        int ladder = 2;
        while (!head.empty() && !tail.empty()) {
            if (head.size() < tail.size()) {
                smallerSet = &head;
                biggerSet = &tail;
            } else {
                smallerSet = &tail;
                biggerSet = &head;
            }
            unordered_set<string> reachableWords; // will be the new smallerSet

            // for any word in head: generate mutations
            // and compare the generated ones with the identical words in biggerSet
            /* effectively: only looking for the intersect of the two sets */
            for (auto it = smallerSet -> begin(); it != smallerSet -> end(); it++) { 
                string word = *it;
                // generate candidates
                for (int i = 0; i < word.size(); i++) {
                    char t = word[i];
                    for (int j = 0; j < 26; j++) {
                        word[i] = 'a' + j;
                        // a coomon mutation between two sets: we are done!
                        if (biggerSet -> find(word) != biggerSet -> end()) {
                            return ladder;
                        }
                        // a non-common but valid mutation: add to the reachable
                        if (dict.find(word) != dict.end()) {
                            reachableWords.insert(word);
                            dict.erase(word);   // remove the valid generated word from dict
                        }
                    }
                    word[i] = t;
                }
            }
            ladder++;
            smallerSet -> swap(reachableWords);   // update the set
        }
        return 0;
    }
};
```

---

## 515. 在每个树行中找最大值

本题秒杀! 分享自己的两个解法：
### 版本一： BFS

```C++
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
```

### 版本二 DFS

```C++
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
    vector<int> res;

    void backtracking(int level, TreeNode* root){
        if(!root){
            return;
        }
        // get a slot for current level
        if(level + 1 > res.size()){
            res.push_back(INT_MIN);
        }
        // process current node
        res[level] = max(res[level], root->val);
        // going down
        backtracking(level + 1, root->left);
        backtracking(level + 1, root->right);
    }
public:
    vector<int> largestValues(TreeNode* root) {
        backtracking(0, root);
        return res;
    }
};
```