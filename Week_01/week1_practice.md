# Week 1 Leetcode Pracetice External/Additional Good Snippets


## 283.移动零
**double pointer**

### 版本一
来自官方题解，仅仅使用了一重```while```loop和```swap()```。

```left```指向非零序列末尾+ 1，```right```用于travese。当```nums[right]```非零就交换且```left++```。

``` C++
void moveZeroes(vector<int>& nums) {
    int n = nums.size(), left = 0, right = 0;
    while (right < n) {
        if (nums[right]) {
            swap(nums[left], nums[right]);
            left++;
        }
        right++;
    }
}
作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/move-zeroes/solution/yi-dong-ling-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二 

来自国际站的解法，记录了目前扫过的区间里所有0的个数（所谓的```snowballSize```滚雪球）。我们先假设扫过区间的0零都连续排列，聚合在一起了，然后一旦发现一个非0的元素```nums[i]```就将之与前边的snowball区间的最前边的0交换，i.e. ```swap(nums[i], nums[i - snowballSize])```。具体题解见[这里](https://leetcode.com/problems/move-zeroes/discuss/172432/THE-EASIEST-but-UNUSUAL-snowball-JAVA-solution-BEATS-100-(O(n))-%2B-clear-explanation)。

``` Java
public void moveZeroes(int[] nums) {
    int snowBallSize = 0; 
    for (int i=0;i<nums.length;i++){
        if (nums[i]==0){
            snowBallSize++; 
        }
        else if (snowBallSize > 0) {
            int t = nums[i];
            nums[i]=0;
            nums[i-snowBallSize]=t;
        }
    }
}
```

---

## 11.盛水容器

### 版本一
该版本本质和我做的版本差不多，只是在更新```i```和```j```的时候再开```while```直接一步到位到下一个比```height[i]```和```height[right]```大的下标。

``` C++
int maxArea(vector<int>& height) {
    int water = 0;
    int i = 0, j = height.size() - 1;
    while (i < j) {
        int h = min(height[i], height[j]);
        water = max(water, (j - i) * h);
        while (height[i] <= h && i < j) i++;
        while (height[j] <= h && i < j) j--;
    }
    return water;
}
```

### 版本二

该版本为Java实现。本质和我做的版本也差不多只是更新下标的顺序不一样。缺点是不够compact和优雅，优点是计算area时width不需要+1。

```Java
 public int maxArea(int[] height) {
    int maxarea = 0, l = 0, r = height.length - 1;
    while (l < r) {
        maxarea = Math.max(maxarea, Math.min(height[l], height[r]) * (r - l));
        if (height[l] < height[r])
            l++;
        else
            r--;
    }
    return maxarea;
}
```

---

## 125.验证回文串

### 在while内加速跳过非字母数字方法：

```C++
bool isPalindrome(string s) {

    int i = 0, j = s.size() - 1;
    while(i < j){
        while(!isalnum(s[i]) && i < j) ++i;
        while(!isalnum(s[j]) && i < j) --j;
        
        if(tolower(s[i++]) != tolower(s[j--])) return false;
    }

    return true;
}
```

---

## 三数之和

### 版本一
许多版本的实现均为先排序（引入```o(logn)```复杂度）。其实我们不需要自己实现排序算法，直接利用```<algorithm>```头文件里现成库函数实现：

```C++
std::sort(nums.begin(), nums.end());
```

之后我们用双指针往中间夹：设从```a[k]```开始，则我们需要在```a[k+1:]```之中找到两个数字使得```a + b == -a[k] == target```。

然后设指针为```int i = i + 1```和```int j = end - 1```，当```a[i] + a[j] == target```自然正好找到一个答案，记录下来；当```a[i] + a[j] < target```，利用单调性（已排好序）我们```i++```; 当```a[i] + a[j] > target```我们```--j```。

中间有部分关于```while```的技巧：用于跳过前后一样的东西以去重。

```C++
vector<vector<int>> threeSum(vector<int>& nums) {
    // sort
    sort(nums.begin(), nums.end());

    // double ptr
    int const LEN = nums.size();
    vector<vector<int>> ans;
    for(int i = 0; i < LEN - 2; ++i){
        // when nums[i] is positive, as nums is sorted there wouldn't be any a+b that is negative and a + b == -nums[i]
        if(nums[i] > 0) break;

        // when i == 0: we can'd do nums[i - 1]; we skip the duplicates
        if(i > 0 && nums[i] == nums[i - 1]) continue;

        int l = i + 1, r = LEN - 1, target = -nums[i];
        while(l < r){
            if(nums[l] + nums[r] < target){
                while(l < r && nums[l] == nums[++l]);
            }
            else if(nums[l] + nums[r] > target){
                while(l < r && nums[r] == nums[--r]);
            }
            else{
                ans.push_back({nums[i], nums[l], nums[r]});

                while(l < r && nums[l] == nums[++l]);
                while(l < r && nums[r] == nums[--r]);
            }
        }
    }

    return ans;
}
```

Leetcode国际站另一个高票Python实现差不多，只是没了那些```while```：

```Python
def threeSum(self, nums):
    res = []
    nums.sort()
    for i in xrange(len(nums)-2):
        if i > 0 and nums[i] == nums[i-1]:
            continue
        l, r = i+1, len(nums)-1
        while l < r:
            s = nums[i] + nums[l] + nums[r]
            if s < 0:
                l +=1 
            elif s > 0:
                r -= 1
            else:
                res.append((nums[i], nums[l], nums[r]))
                while l < r and nums[l] == nums[l+1]:
                    l += 1
                while l < r and nums[r] == nums[r-1]:
                    r -= 1
                l += 1; r -= 1
    return res
```

---

## 34.排序数组中查找元素的第一个和最后一个位置
和THU邓版DSA返回最靠右的不小于target的二分查找不同，Leetcode官方题解与许多题解版本的二分查找是返回**第一个大于或等于**target的下标（the left index, the leftmost one）以及**第一个大于**target的下标（the right index, the rightmost one）。

其主要区别是其切分点。对于求leftmost index的：切分点为```e <= a[mid]```。
```C++
while(left <= right){
    int mid = (left + right) >> 1; 
    if(e <= a[mid]){
        right = mid - 1;
        ans = mid;
    }
    else{
        left = mid + 1;
    }
}
return ans;

```

至于求rightmost的：切分点为```e < a[mid]```。
```C++
while(left <= right){
    int mid = (left + right) >> 1; 
    if(e < a[mid]){
        right = mid - 1;
        ans = mid;
    }
    else{
        left = mid + 1;
    }
}
return ans;

```

完整版代码：
```C++
int binarySearch(vector<int>& nums, int target, bool lower) {
    int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] > target || (lower && nums[mid] >= target)) {
            right = mid - 1;
            ans = mid;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int leftIdx = binarySearch(nums, target, true);
    int rightIdx = binarySearch(nums, target, false) - 1;
    if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
        return vector<int>{leftIdx, rightIdx};
    } 
    return vector<int>{-1, -1};
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/solution/zai-pai-xu-shu-zu-zhong-cha-zhao-yuan-su-de-di-3-4/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 反转列表

### 递归版 （来自国际版官方题解）
The recursive version is slightly trickier and the key is to work backwards. Assume that the rest of the list had already been reversed, now how do I reverse the front part? Let's assume the list is: n1 → … → nk-1 → nk → nk+1 → … → nm → Ø

Assume from node nk+1 to nm had been reversed and you are at node nk.

n1 → … → nk-1 → nk → nk+1 ← … ← nm

We want nk+1’s next node to point to nk.

So,

nk.next.next = nk;

Be very careful that n1's next must point to Ø. If you forget about this, your linked list has a cycle in it. This bug could be caught if you test your code with a linked list of size 2.


``` C++
ListNode* reverseList(ListNode* head) {
    if(!head || !(head->next)) return head;
    
    ListNode* list = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return list;
}
```

---

## 24. 两两交换链表中的节点

### 递归版
```C++
 ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newHead = head->next;
        head->next = swapPairs(newHead->next);
        newHead->next = head;
        return newHead;
    }

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs/solution/liang-liang-jiao-huan-lian-biao-zhong-de-jie-di-91/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### K个一组翻转特殊情况(本人实现改写)
本题实质是[25]题的```k = 2```的特殊情况，因此可以直接套用。当中```reverse()```操作还可以进一步优化使得不需要在k组后加```end->next = nullptr;```：

```C++
ListNode* swapPairs(ListNode* head) {
    ListNode* hair = new ListNode(0, head);
    ListNode* prev = hair, *end = hair;
    
    while(end->next){
        for(int i = 0; i < 2 && end; ++i){
            end = end->next;
        }
        if(!end) break;
        
        ListNode* start = prev->next, *next = end->next;
        
        // swap
        start->next = next;
        end->next = start;
        prev->next = end;
        
        // update
        prev = start;
        end = prev;
    }
    
    head = hair->next;
    delete hair;
    return head;
}
```

---

## 66.加一

基本思路大体相同，只是在999...999 + 1的时候可以经过了中间```for```循环处理后，我们可以直接让最高位```digits[0] = 1```然后数组最后边补一个0：
```digits.push_back(0);```。

注意```for```循环的条件应该为```i >= 0```！

```C++
vector<int> plusOne(vector<int>& digits) {
    int const LEN = digits.size();
    
    for(int i = LEN - 1; i >= 0; --i){
        if(digits[i] == 9){
            digits[i] = 0;
        }
        else{
            ++digits[i];
            return digits;
        }
    }
    
    digits[0] = 1;
    digits.push_back(0);
    return digits;
}
```

---

## 20.有效括号

为了减少代码量增加代码复用我们可以把配对的括号放进一个```unordered_map<char, char>```里。下面的实现基于自己的的```switch```实现：

```C++
bool isValid(string s) {
    stack<char> S;
    int n = s.size();

    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    for(int i = 0; i < n; i++){
        char c = s[i];
        switch(c){
            case '}':
            case ']':
            case ')':
                if(!S.empty() && S.top() == pairs[c]){
                    S.pop();
                }
                else{
                    return false;
                }
                break;
            case '{':
            case '[':
            case '(':
                S.push(c);
        }
    }

    return S.empty();
}
```

---
## 155.最小栈

### 版本一
本版本使用```pair```且仅用一个栈实现。这里的的内部栈为```stack<pair<int,int>>```类型，其```first```为正常数据，```second```为其对应的全栈最小值。

```C++
class MinStack {
private:
    stack<pair<int, int>> st;

public:
    MinStack() {
    }
    
    void push(int x) {
        if (st.size() == 0) {
            st.push({x, x});
        } else {
            st.push({x, min(x, st.top().second)});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

作者：fuxuemingzhu
链接：https://leetcode-cn.com/problems/min-stack/solution/zui-yi-dong-yi-ge-zhan-tong-shi-bao-cun-dang-qian-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 21. 合并两个有序链表

### 递归版

```Java
class Solution {
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null) {
            return l2;
        } else if (l2 == null) {
            return l1;
        } else if (l1.val < l2.val) {
            l1.next = mergeTwoLists(l1.next, l2);
            return l1;
        } else {
            l2.next = mergeTwoLists(l1, l2.next);
            return l2;
        }

    }
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/merge-two-sorted-lists/solution/he-bing-liang-ge-you-xu-lian-biao-by-leetcode-solu/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 84. 柱状图中最大的矩形

### 版本一 （中文leetcode官方最优解）

该版本开了两个```vector```，一个用于存左边界，另一个用于存右边界。而且用了两遍```for``` loop，一个用于求各个```heights[i]```所对应的左右边界index，另一个loop用于求解面积。复杂度依旧为```O(n)```。个人认为实际上完全可以用一遍循环解决。

然而此处我们依旧贴出代码：
```C++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n, n);
        
        stack<int> mono_stack;
        for (int i = 0; i < n; ++i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                right[mono_stack.top()] = i;
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
            mono_stack.push(i);
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/zhu-zhuang-tu-zhong-zui-da-de-ju-xing-by-leetcode-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二
此解答来自国际版，cn版有类似解法。本版本有两个特点:
1. 用```vector```模拟栈，很快；
2. 只用了一遍循环，虽然大体逻辑和版本一类似

开头技术处理比较tricky：有一句```height.push_back(0);```。这是因为如果没有这一句，当```for```循环中```i == heigh.size() - 1```时，我们处理的是```i < height.size() - 1```也即末尾之前的东西，而且最后才执行```index.push_back(i)```，导致最末尾的这个棒子根本没有机会被计算。因此，我们需要加一个额外的棒子在```heights```末尾，使得我们可以处理```heights[heights.size() - 1]```。

该额外元素选取也很讲究，千万不可以高，因此我们选取不大于0的值。此处我们选0。

至于looping condition中的```height[index.back()] >= height[i]```的```>=```号：我们认为当两者相等时，虽然不至于可以肯定地确定```height[index.back()]```的右边界，但可以肯定其有边界至少不小于```i```：我们不妨先将其计算了，反正```height[index.back()]```的左边界将一直在，而且我们早晚会刚好扫描到他的真正有边界。当```for```的```i```扫描原来的```height[index.back()]```的真正右边界时，我们就能计算出来，将其更新在最大值```ret```。

```C++
int largestRectangleArea(vector<int> &height) {
        int ret = 0;
        height.push_back(0);    // important!
        vector<int> index;
        
        for(int i = 0; i < height.size(); i++)
        {
            while(index.size() > 0 && height[index.back()] >= height[i])
            {
                int h = height[index.back()];
                index.pop_back();
                
                int sidx = index.size() > 0 ? index.back() : -1;
                if(h * (i - sidx - 1) > ret)
                    ret = h * (i-sidx-1);
            }
            // attention: if we don't append when i == height.size() - 1, we can never process that height. 
            // We need an extra bar (with zero or negative height) in order to process it
            index.push_back(i);
        }
        
        return ret;
    }
```