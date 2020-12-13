# Week 2 Leetcode Practice Additional/Good Snippets

## 242.有效字母异位词

### 版本一： 稍微更高效的unordered_map

来自国际版。比起自己的笨重的```unordered_map<char, int>```版本实现稍微更加高效。在遍历哈希表时利用了按元素遍历```for```循环的特性（range-based for lop since C++ 11，这是本人极少用的）。

```C++
bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        int n = s.length();
        unordered_map<char, int> counts;
        for (int i = 0; i < n; i++) {
            counts[s[i]]++;
            counts[t[i]]--;
        }
        for (auto count : counts)
            if (count.second) return false;
        return true;
    }
```
至于其他的版本大同小异。

---

## 49. 字母异位词分组

### 版本一

该版本和主流最右版本区别不大，但是在字符串排序阶段利用了字符只有26个小写字母的特点，使用counting sort而非```std::sort()```的快排，进一步提升了运行效率。

```C++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string s : strs) {
            // counting sort结果作为key
            mp[strSort(s)].push_back(s);
        }
        vector<vector<string>> anagrams;
        for (auto p : mp) { 
            anagrams.push_back(p.second);
        }
        return anagrams;
    }
private:
    string strSort(string s) {
        int counter[26] = {0};
        for (char c : s) {
            counter[c - 'a']++;
        }
        string t;
        for (int c = 0; c < 26; c++) {
            t += string(counter[c], c + 'a');
        }
        return t;
    }
};
```

---

## 42. 接雨水

本题本应该为上周（week 2）内容。属于单调栈的应用。

### 版本一：暴力解
讨论暴力解的价值在于讨论如何切分、划分水量使之可以被计算。简单说，对于每个元素```height[i]```，其单个贡献的水量(其垂直方向上的积水量)可这么看：

> 从i往左看（直到下标0）最高柱子的高度```left_max[i]```;从i往右看（直到下标LEN - 1）最高柱子高度为```right_max[i]```；则在```height[i]```处积累的水量应为：```min(left_max[i], right_max[i])```（短板效应），减去本处的高度```height[i]```，再乘上宽度1，即：
>
> ```min(left_max[i], right_max[i]) - height[i]```
>
> 只需要不断迭代每个```i```，将结果累加即可。

因此，对每个```height[i]```我们都要搜寻其左侧和右侧的最大柱子长度，时间复杂度为```O(n^2)```。

```C++
int trap(vector<int>& height)
{
    int ans = 0;
    int size = height.size();
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { //Search the left part for max bar size
            max_left = max(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { //Search the right part for max bar size
            max_right = max(max_right, height[j]);
        }
        ans += min(max_left, max_right) - height[i];
    }
    return ans;
}

作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二：DP

本DP解为上一版本之优化，对求到的```left_max```们记录下来。也即，各用一次遍历记录各个```height[i]```所对应的从自己出发向左侧、向右侧的最长柱子下标。最后再来一次```for```遍历求```min(left_max[i], right_max[i]) - height[i]```。

具体地，对于求```left_max```，状态方程为：

```
left_max[i] = max(left_max[i - 1], height[i]), for i >= 1;

left_max[i] = height[i],                       for i == 0;
```
解释如下：当```i == 0```，其左侧只有自己，自然为```height[i]```。

```i >= 1```时，```left_max[i - 1]```为从```height[0]```到```height[i - 1]```之中最值。而则```left_max[i]```为从```height[0]```到```height[i]```之中最值，自然为```left_max[i - 1]```和新的```height[i]```比较之较大者。

对于求```right_max```有类似逻辑。为完整性仅列出状态方程：
```
right_max[i] = max(right_max[i + 1], height[i]), for 0 <= i <= LEN - 2;

right_max[i] = height[LEN - 1],                  for i == LEN - 1;
```
完整代码如下：
```C++
int trap(vector<int>& height)
{
    if (height == null)
        return 0;
    int ans = 0;
    int size = height.size();
    vector<int> left_max(size), right_max(size);
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = max(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = max(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
}

作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本三：double pointer

还是左右指针```left```和```right```两边夹，同时有```int```变量```left_max```和```right_max```分别记录0到```left```以及```right```到```LEN - 1```之中的最值。

当```height[left]```小于```left_max```时，说明在```left```处可能会形成低洼。若再加上```height[left] < height[right]```，我们可以断言在left的右侧肯定至少有一根比较高的柱子，足以使得在```left```处形成一个低洼。我们只需要加上在```left```处竖直方向上积累的水即可。

```right```一侧同理。看代码：

```C++
int trap(vector<int>& height)
{
    int left = 0, right = height.size() - 1;
    int ans = 0;
    int left_max = 0, right_max = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
            ++left;
        }
        else {
            height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
            --right;
        }
    }
    return ans;
}

作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

其时间复杂度为```O(n)```然而我们不需要额外数组只需要一维变量，空间复杂度为```O(1)```。

### 版本四

欣赏大佬的鬼才...Orz

[传送门](https://leetcode.com/problems/trapping-rain-water/discuss/17364/7-lines-C-C%2B%2B)在此！

```C++
int trap(vector<int>& height) {
    int l = 0, r = height.size()-1, level = 0, water = 0;
    while (l < r) {
        int lower = height[height[l] < height[r] ? l++ : r--];
        level = max(level, lower);
        water += level - lower;
    }
    return water;
}
```

---
## 590. N叉树后序遍历

### 版本一： 纯迭代版

```Python
class Solution(object):
    def postorder(self, root):
        """
        :type root: Node
        :rtype: List[int]
        """
        if root is None:
            return []
        
        stack, output = [root, ], []
        while stack:
            root = stack.pop()
            if root is not None:
                output.append(root.val)
            for c in root.children:
                stack.append(c)
                
        return output[::-1]

作者：LeetCode
链接：https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/solution/ncha-shu-de-hou-xu-bian-li-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

等效的C++版本如下：
```C++
vector<int> postorder(Node* root) {
    if(root==NULL) return {};
    vector<int> res;
    stack<Node*> stk;
    stk.push(root);
    while(!stk.empty())
    {
        Node* temp=stk.top();
        stk.pop();
        for(int i=0;i<temp->children.size();i++) stk.push(temp->children[i]);
        res.push_back(temp->val);
    }
    reverse(res.begin(), res.end());
    return res;
}
```
---

## 剑指 Offer 40. 最小的k个数

### 版本一： 快排思想

我们知道快排的划分函数每次执行完后都能将数组分成两个部分，小于等于分界值 pivot 的元素的都会被放到数组的左边，大于的都会被放到数组的右边，然后返回分界值的下标。本解法的辅助函数```partition()```正是快排中的分割算法；而```randomized_partition()```不过是使得```partition()```时随机挑选一个```pivot```而非永远是最后一个。

```randomized_selected(vector<int>& nums, int l, int r, int k)```是本解法的核心逻辑，其切分```arr```数组的```[l,r]```闭区间部分，同时保证```pivot```前（含```pivot```自己）必有```k```个（小于或等于```pivot```的）数字。

```randomized_selected()```不断调用```randomized_partition()```。假设```randomized_partition()```返回切分下标```pos```，则原理如下：
* 后返回的下标```pos - l + 1 == k```，则```[l, pos]```之间刚好有```k```个元素，可以立即返回。此为**递归基**！！
* ```pos - l + 1 < k```，说明还需要从```[pos, r]```中再要额外的```k - (pos - l + 1```个数字使得有```k```个符合要求元素。如何要？递归调用```randomized_partition(arr, pos + 1, r, k - (pos - l + 1))```。该例程不动原```[l, pos]```，往```[pos+1, r]```寻求切分，直至触发递归基。
* ```pos - l + 1 > k```, 说明```[l, pos]```长度太长, 最小的```k```个数字在```[l, pos - 1]```之间，需要在该区间进一步。我们递归调用```randomized_partition(arr, l, pos - 1, k)```直到触发递归基。

至于```getLeastNumbers()```则是包装接口。稍作处理后返回。

该算法平均时间复杂度```O(n)```，最坏```O(n^2)```。

``` C++
class Solution {
    int partition(vector<int>& nums, int l, int r) {
        int pivot = nums[r];
        int i = l - 1;
        for (int j = l; j <= r - 1; ++j) {
            if (nums[j] <= pivot) {
                i = i + 1;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }
    // 基于随机的划分
    int randomized_partition(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }
    void randomized_selected(vector<int>& arr, int l, int r, int k) {
        if (l >= r) {
            return;
        }
        int pos = randomized_partition(arr, l, r);
        int num = pos - l + 1;
        if (k == num) {
            return;
        } else if (k < num) {
            randomized_selected(arr, l, pos - 1, k);
        } else {
            randomized_selected(arr, pos + 1, r, k - num);
        }
    }
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        srand((unsigned)time(NULL));
        randomized_selected(arr, 0, (int)arr.size() - 1, k);
        vector<int> vec;
        for (int i = 0; i < k; ++i) {
            vec.push_back(arr[i]);
        }
        return vec;
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/solution/zui-xiao-de-kge-shu-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 347. Top K frequent elements

### 版本一：priority_queue + map 更简洁写法

原理与我的一致，只是写法更简洁：实际上由于```priority_queue```默认为max heap，可以少写一些参数。如下：

``` C++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        for(int num : nums){
            map[num]++;
        }
        
        vector<int> res;
        // pair<first, second>: first is frequency,  second is number
        priority_queue<pair<int,int>> pq; 
        for(auto it = map.begin(); it != map.end(); it++){
            pq.push(make_pair(it->second, it->first));
            if(pq.size() > (int)map.size() - k){
                res.push_back(pq.top().second);
                pq.pop();
            }
        }
        return res;
    }
};
```

## 版本二：基于桶排序
将所有数字用哈希表统计后，创建一个```vector<vector<int>>```变量```buckets```：长度为```nums.size() + 1```（因为有频次为0），```buckets[i]```为频次为```i```的所有数字集合。因此，```buckets```数组越靠后，含有频次越大的数字。

最后，只需要从```buckets```后边开始取，取够```k```个数字即可。

```C++
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    for (int num : nums)
        ++m[num];
    
    vector<vector<int>> buckets(nums.size() + 1); 
    for (auto p : m)
        buckets[p.second].push_back(p.first);
    
    vector<int> ans;
    for (int i = buckets.size() - 1; i >= 0 && ans.size() < k; --i) {
        for (int num : buckets[i]) {
            ans.push_back(num);
            if (ans.size() == k)
                break;
        }
    }
    return ans;
}
```

---

## 剑指 Offer 49. 丑数 与 264. 丑数 II

### 版本一：动态规划
堆解法太慢了！本动态规划解法实质上和堆解法的内核一样：都是对于下一个丑数，分别乘2、乘3、乘5地计算下一个丑数。

在PQ解法中，我们使用```priority_queue```跟踪算出来的新丑数大小以决定下一个丑数是哪个（```push```后，pq顶部即为下一个丑数，只是每次插入都要```O(logn)```极慢），以及需要一个```while()```循环去重，使得很慢。

不同的是，本解法手动用```min()```决定哪一个是下一个丑数；另外有三个指针可以帮助不重不漏。我们这里指出，这三个指针```two```、```three```、```five```，实质是指向**有资格同i相乘的最小丑数的位置**。其算法如下：

1. 我们先建立一个长度为 ```n``` 的 ```dp``` 数组，```dp[i]``` 表示第 ```i + 1``` 个丑数。
2. 然后我们设立三个变量：```two```, ```three```, ```five```，它们都代表 ```dp``` 数组中的索引。我们通过选取 ```dp[two] * 2```, ```dp[three] * 3``` 和 ```dp[five] * 5 中的最小值来确定下一个丑数的值。
3. 当找到了下一个丑数后，假如这个丑数是由 ```two``` 得来的，我们就 ```++ two```；假如是由 ```three``` 得来的，我们就 ```++ three```；是由 ```five``` 得来的，我们就 ```++ five```。这样就可以保证每个丑数都会被找出来。

``` C++
class Solution {
public:
    int nthUglyNumber(int n) {
        int two = 0, three = 0, five = 0;
        vector<int> dp(n);
        dp[0] = 1; // dp 初始化

        for (int i = 1; i < n; ++i) {
            int t1 = dp[two] * 2, t2 = dp[three] * 3, t3 = dp[five] * 5;
            dp[i] = min(min(t1, t2), t3);

            if (dp[i] == t1) {++ two;}
            if (dp[i] == t2) {++ three;}
            if (dp[i] == t3) {++ five;}
        }

        return dp[n - 1];
    }
};

作者：superkakayong
链接：https://leetcode-cn.com/problems/chou-shu-lcof/solution/zi-jie-ti-ku-jian-49-zhong-deng-chou-shu-1shua-by-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```