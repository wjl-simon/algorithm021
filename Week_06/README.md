# Week 6 Leetcode Additional / Good Snippets

## 53. 最大子序和
### 版本一：DP with O(1) space complexity
原po来自国际站一solution的评论区：[传送门](https://leetcode.com/problems/maximum-subarray/discuss/20189/Simplest-and-fastest-O(n)-C%2B%2B-solution)。

考虑到DP方程为```dp[i] = min(dp[i - 1] + nums[i], nums[i])```，仅仅用到了```dp[i - 1]```的信息，我们完全可以只用一个变量维护（也即下边所谓的```int_local_max```。至于```int_global_max```则是```dp[]```中之最（也即各个```int_local_max```的最大值）。

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        else if (nums.size() == 1) return nums.at(0);
        
        int int_local_max = nums[0], int_global_max = nums[0];
        size_t sz_length  = nums.size();
        for (size_t i = 1; i != sz_length; ++i) {
            int_local_max  = max(int_local_max + nums[i], nums.[i]);
            int_global_max = max(int_local_max, int_global_max);
        }
        
        return int_global_max;
    }
};
```
---

## 152. 乘积最大子数组

### 版本一：DP O(1)空间优化
显然，对于```f_min[i]```（也即下面```dp_max```）和```f_max[i]```（也即下面```dp_min```）的更新里也只用到了```i - 1```的信息，因此我们不需要开数组。

然而要注意，因为先更新```f_max```，后面更新```f_min```的时候要用到```f_max```的旧值，我们需要再开```temp1```和```temp2```（其实只需要```temp1```）储存旧值，否则会出错。

```C++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int const LEN = nums.size();
        int dp_max = nums[0], dp_min = nums[0];
        int ans = dp_max;
        
        for(int i = 1; i < LEN; ++i){
            int temp1 = dp_max, temp2 = dp_min;
            dp_max = max( max(temp1 * nums[i], nums[i]), temp2 * nums[i] );
            dp_min = min( min(temp2 * nums[i], nums[i]), temp1 * nums[i] );
            ans = max(dp_max, ans);
        }
        return ans;
    }
};
```

### 版本二：双指针
来自[国际站](https://leetcode.com/problems/maximum-product-subarray/discuss/183483/JavaC%2B%2BPython-it-can-be-more-simple)，欣赏...

解释如下：指针在遇到正的```A[i]```则继续与当前```A[i]```或者```A[n - 1 - i]```累乘，当遇到负的```A[i]```则重置为1。每一步，我们都记录当前最大值：```res = max(res, max(left, right));```。

```C++
int maxProduct(vector<int> A) {
    int n = A.size(), res = A[0], left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        left =  (left ? left : 1) * A[i];
        right =  (right ? right : 1) * A[n - 1 - i];
        res = max(res, max(left, right));
    }
    return res;
}
```

```Python
def maxProduct(self, A):
    B = A[::-1]
    for i in range(1, len(A)):
        A[i] *= A[i - 1] or 1
        B[i] *= B[i - 1] or 1
    return max(A + B)
```

---
## 322. 零钱兑换

### 版本一：Top-down DP
由于DP方程为:
```
dp[n] = min_k(dp[n - k]) + 1
```
自然的这非常适合直接用于递归。

```C++
class Solution {
    \// count[i] is the min no. of coins to make up an amount of i + 1 dollars
    vector<int>count;

    int dp(vector<int>& coins, int amount) {
        if (amount < 0) return -1;
        if (amount == 0) return 0;

        // has been computed: return the computed result
        if (count[amount - 1] != 0) return count[amount - 1];

        // the min no. of coins
        int Min = INT_MAX;
        for (int coin:coins) {
            int res = dp(coins, amount - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[amount - 1] = Min == INT_MAX ? -1 : Min;
        return count[amount - 1];
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/coin-change/solution/322-ling-qian-dui-huan-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二：BFS
如超哥视频所说，如果用纯递归方式我们将得到递归树：根节点为```amount```，节点的值为剩余amount，。可以观察到，递归树的深度即为需要的硬币数，则我们只需要找到剩余为0的最浅节点即可。既然是找最浅节点，BFS呼之欲出。

这里的技术细节里，为了达到剪纸作用我们对```coins[]```提前排序（当剩余amount小于```coins[j]```那么更大面额的硬币不需要考虑了），而且我们引入```visited[i]```数组记录是否已计算过的剩余amount为```i```的节点。

下面代码中的step即为深度，也即所需的最少硬币数，也即最终答案。

```Java
public class Solution {

    public int coinChange(int[] coins, int amount) {
        if (amount == 0) {
            return 0;
        }

        Queue<Integer> queue = new LinkedList<>();
        boolean[] visited = new boolean[amount + 1];

        visited[amount] = true;
        queue.offer(amount);

        // 排序是为了加快广度优先遍历过程中，对硬币面值的遍历，起到剪枝的效果
        Arrays.sort(coins);

        int step = 1;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                Integer head = queue.poll();
                for (int coin : coins) {
                    int next = head - coin;
                    // 只要遇到 0，就找到了一个最短路径
                    if (next == 0) {
                        return step;
                    }

                    if (next < 0) {
                        // 由于 coins 升序排序，后面的面值会越来越大，剪枝
                        break;
                    }

                    if (!visited[next]) {
                        queue.offer(next);
                        // 添加到队列的时候，就应该立即设置为 true
                        // 否则还会发生重复访问
                        visited[next] = true;
                    }
                }
            }
            step++;
        }
        // 进入队列的顶点都出队，都没有看到 0 ，就表示凑不出当前面值
        return -1;
    }
}

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/coin-change/solution/dong-tai-gui-hua-shi-yong-wan-quan-bei-bao-wen-ti-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

---

## 198. 打家劫舍

### 版本一：二维数组DP
来自超哥视频。定义状态为二维：```dp[LEN][2]```，解释如下：第一维是规模为```i```问题的解，第二维可取值0（表示不偷第```i```个房子）或者1（表示偷第```i```个房子） i.e. ```dp[n][0]```表示不偷第```n```个房子的情况下的解。

因此，dp方程如下：
```
dp[i][0] = max(dp[i - 1][0], dp[i - 1][1])
dp[i][1] = dp[i - 1][0] + nums[i]

P(i) = max(dp[i][0], dp[i][1])
```
解释如下：```dp[i][0]```是不偷第```i```个房情况下最优解：要么是第```i - 1```不偷时的最优，也或者是第```i - 1```偷的最优，反正不偷第```i```。

```dp[i][1]```说明我们偷第```i```个房子，这要求第```i - 1```必须不能偷，也即```dp[i - 1][0]```，然后再加上第```i```个房子的价值```nums[i]```即可。

而问题规模为```i```的解必定来自```dp[i][0]```, ```dp[i][1]```二者之间。

```C++
class Solution {
public:
    int rob(vector<int>& nums) {
        int const LEN = nums.size();
        if(LEN == 0){
            return 0;
        }

        vector<vector<int>> dp(LEN, vector<int>(2, 0));
        // initialise
        dp[0][0] = 0;
        dp[0][1] = nums[0];

        for(int i = 1; i < LEN; ++i){
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + nums[i];
        }
        return max(dp[LEN - 1][0], dp[LEN - 1][1]);
    }
};
```

---
## 121. 买卖股票的最佳时机

### 版本一： 二维数组状态DP
[传送门](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/bao-li-mei-ju-dong-tai-gui-hua-chai-fen-si-xiang-b/)

> ```dp[i][j]```：下标为 ```i``` 这一天结束的时候，手上持股状态为 ```j``` 时，我们持有的```现金数```。

(笔者注：现金数不等于profit，现金数是本金 + profit，但是只要我们假设本金为0那么现金数的数值上等于profit,最后可以直接输出```d[len - 1][0]```)。
>
> ```j = 0```，表示当前不持股；
> ```j = 1```，表示当前持股。
> 注意：这个状态具有前缀性质，下标为 ```i``` 的这一天的计算结果包含了区间 [0, i] 所有的信息，因此最后输出 ```dp[len - 1][0]```。

DP方程如下：
```
dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i])
dp[i][1] = max(dp[i - 1][1], -prices[i])
```
解释如下：
> ```dp[i][0]```：规定了今天不持股，有以下两种情况：
> * 昨天不持股，今天什么都不做；
> * 昨天持股，今天卖出股票（现金数增加），
> 
> ```dp[i][1]```：规定了今天持股，有以下两种情况：
> * 昨天持股，今天什么都不做（现金数增加）；
> * 昨天不持股，今天买入股票（注意：只允许交易一次，因此手上的现金数就是当天的股价的相反数）。

代码如下：
```Java
public class Solution {

    public int maxProfit(int[] prices) {
        int len = prices.length;
        // 特殊判断
        if (len < 2) {
            return 0;
        }
        int[][] dp = new int[len][2];

        // dp[i][0] 下标为 i 这天结束的时候，不持股，手上拥有的现金数
        // dp[i][1] 下标为 i 这天结束的时候，持股，手上拥有的现金数

        // 初始化：不持股显然为 0，持股就需要减去第 1 天（下标为 0）的股价
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        // 从第 2 天开始遍历
        for (int i = 1; i < len; i++) {
            dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = Math.max(dp[i - 1][1], -prices[i]);
        }
        return dp[len - 1][0];
    }
}

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/bao-li-mei-ju-dong-tai-gui-hua-chai-fen-si-xiang-b/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

由于DP方程只用到了```dp[i - 1][0]```和```dp[i - 1][1]```，我们可以做空间优化（O(1)空间复杂度）：
```Java

public class Solution {

    public int maxProfit(int[] prices) {
        int len = prices.length;
        if (len < 2) {
            return 0;
        }

        int[] dp = new int[2];
        dp[0] = 0;
        dp[1] = -prices[0];
        for (int i = 1; i < len; i++) {
            dp[0] = Math.max(dp[0], dp[1] + prices[i]);
            dp[1] = Math.max(dp[1], -prices[i]);
        }
        return dp[0];
    }
}

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/bao-li-mei-ju-dong-tai-gui-hua-chai-fen-si-xiang-b/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二： 一次遍历
本题解实际是用一维DP数组的空间优化版：keep track of the greatest difference of prices from day 0 to day i.

```Java
public class Solution {
    public int maxProfit(int prices[]) {
        int minprice = Integer.MAX_VALUE;
        int maxprofit = 0;
        for (int i = 0; i < prices.length; i++) {
            if (prices[i] < minprice) {
                minprice = prices[i];
            } else if (prices[i] - minprice > maxprofit) {
                maxprofit = prices[i] - minprice;
            }
        }
        return maxprofit;
    }
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/121-mai-mai-gu-piao-de-zui-jia-shi-ji-by-leetcode-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```