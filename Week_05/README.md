# Week 5 Leetcode Additional Good Snippets

## 51. n皇后

### 版本一
显然，每个皇后必须位于不同行和不同列，因此将 NN 个皇后放置在 N \times NN×N 的棋盘上，一定是每一行有且仅有一个皇后，每一列有且仅有一个皇后，且任何两个皇后都不能在同一条斜线上。基于上述发现，可以通过回溯的方式寻找可能的解。

其中，方向一的斜线为从左上到右下方向（正对角线），同一条斜线上的每个位置满足**行下标与列下标之差**相等。

方向二的斜线为从右上到左下方向（反对角线），同一条斜线上的每个位置满足**行下标与列下标之和**相等。

```C++
class Solution {
public:
    // 存放结果的数组
    vector<vector<string>> result;
    vector<vector<string>> solveNQueens(int n) 
    {
        result.clear();
        vector<string>temp_checkboard(n,string(n,'.'));
        backtrack(0,n,temp_checkboard);
        return result;
    }

    //回溯基本框架 确定参数----当前皇后行、棋盘的大小、存储排序结果的棋盘
    void backtrack(int row,int n,vector<string>& checkboard)
    {
        //确定终止条件
        if(row == n)
        {
            result.push_back(checkboard);
            return;
        }
        //还需要特定的剪枝----针对特定的行和列 --对每一个都要试
        for(int col = 0; col < n; ++col)
        {
            if(isVaild(row,col,checkboard,n))   //剪枝--必须是有效的位置
            {
                checkboard[row][col] = 'Q';
                backtrack(row+1,n,checkboard);
                checkboard[row][col] = '.';
            }
        }
    }
    //判断皇后当前所在的位置是否有效
    bool isVaild(int row,int col,vector<string>& checkboard,int n)
    {
        //检查列
        for(int i = 0; i < row;++i)
        {
            if(checkboard[i][col] == 'Q')
                return false;
        }
        //检查正对角线
        for(int i = row-1,j = col-1;i >= 0 && j >= 0;--i,--j)
        {
            if(checkboard[i][j] == 'Q')
                return false;
        }
        //检查反对角线
        for(int i = row-1,j = col+1; i >= 0 && j < n;--i,++j)
        {
            if(checkboard[i][j] == 'Q')
                return false;
        }
        return true;
    }
};
```

---

## 62. 不同路径

### 版本一： 递归版DP

```Java
public int uniquePaths(int m, int n) {
    return uniquePathsHelper(1, 1, m, n, new HashMap<>());
}

public int uniquePathsHelper(int i, int j, int m, int n, Map<String, Integer> map) {
    if (i > m || j > n)
        return 0;
    if ((i == m && j == n))
        return 1;
    String key = i + "*" + j;
    if (map.containsKey(key))
        return map.get(key);
    int right = uniquePathsHelper(i + 1, j, m, n, map);
    int down = uniquePathsHelper(i, j + 1, m, n, map);
    int totla = right + down;
    map.put(key, totla);
    return totla;
}

作者：sdwwld
链接：https://leetcode-cn.com/problems/unique-paths/solution/dong-tai-gui-hua-di-gui-gong-shi-deng-3z-9mp1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 版本二：不同的状态变量设置（来自超哥）
（来自超哥）和LC上主流解法大体思路一致，只是数组```dp```设置不一样：此处```dp[i][j]```为从(i, j)到达(m - 1, n - 1)的走法。

```C++
class Solution {
public:
    int uniquePaths(int m, int n) {
        // no. of paths from (i, j) to (m - 1, n - 1)
        vector<vector<int>> dp(m, vector<int>(n, 0));
       for(int i = m - 1; i >= 0; --i){
           for(int j = n - 1; j >= 0; --j){
               if(i == m - 1 || j == n - 1){
                   dp[i][j] = 1;
               }
               else{
                   dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
               }
           }
       }
       return dp[0][0];
    }
};
```

### 版本三：仅使用DP数组
本解法是上一解法的空间复杂度优化（O(n)）。注意到DP方程```dp[i][j] = dp[i - 1][j] + dp[i][j - 1]```，实际上```dp[i][j]```不过是用到了上一行(```dp[i - 1]```)的信息，而且上一行的信息的下标也是```j```。至于来自本行```i```的信息不过是```dp[i][j - 1]```。

因此。我们可以仅用一维数组```vector<int> dp(n, 0)``` (和列数同size):
* 当```i == 0```时（也即第0行），老实initilise；
* 当```i > 0```，我们的dp数组已经有了来自上一行信息；我们要算原来的```dp[i][j] = dp[i - 1][j] + dp[i][j - 1]```，不过是需要```dp[j] = dp[j] + dp[j - 1]```。

```C++
class Solution {
public:
    int uniquePaths(int m, int n) {
        // no. of paths from (0, 0) to (i, j)
        vector<int> dp(n);

        // initialise for row 0
        for(int j = 0; j < n; ++j){
            dp[j] = 1;
        }
        // solve
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};
```