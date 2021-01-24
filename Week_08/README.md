# Week8

## 190. 颠倒二进制位

### 版本一：巧用while少移动
来自提交运行时间分布sample，用```while```判断数字```n```为0后提前终止程序。

```C++
class Solution {
  public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0, power = 31;
    while (n != 0) {
      ret += (n & 1) << power;
      n = n >> 1;
      power -= 1;
    }
    return ret;
  }
};
```

### 版本二
本版本每次取n```n```的最低位直接加，但是在加之前左移```ans```。和超哥给的取到最低位后将其直接左移到对应的位置上不同。

```C++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;

        for(int i = 0; i < 32; ++i){
            ans <<= 1;
            ans += (n & 1);
            n >>= 1;
        }
        return ans;
    }
};
```