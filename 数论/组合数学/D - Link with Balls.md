#   🍀[D - Link with Balls ](https://vjudge.net/contest/461347#problem/D)


   为什么有这么神仙的题，呜呜呜，我好想写出来一个神仙题呀！！！
   yzgg告诉我的时候，感觉身临其境，被骂惨了！！
 ![image](https://user-images.githubusercontent.com/92497177/198069800-f14a76b3-e7ca-43e7-8689-9af143eb2fed.png)
  
   
   
##   先找出来十分关键的规律  

   第一步十分的离谱，这TM是人能想出来的？
  
  编号  |   表示的范围
  ----  | -----
  1     |    k * 1
  2     |    1
  3     |    k * 2
  4     |    1, 2
  5     |    k * 3
  6     |    1, 2, 3
  
  我们观察一下，对于编号为1的桶，我们可以拿出所有数量的球  
  我们如果将2和3结合一下，那它可以表示出来， $2 * k + 1,  2 * k$
  我们将4和5结合一下， 那他可以表示出来  $3 * k, 3 * k + 1, 3 * k + 2$ 
  最后一个可以表示出来1 - n的所有数
  
  所以我们就发现了一个离谱的现象， 我们可以将其分理出n个可以拿出任何个数球的桶和一个可以拿出n以内的数量的桶
  
  
  此时我们就要利用到一个排列组合种最常见的方法了

## 隔板法

  我们假设 $m > n$
  
  我们此时可以枚举最后一个桶拿出了几个，那么我们需要求的方案数就是 $\sum\limits_{x=0}^{n}{{m - x + n -1}\choose{n - 1}}$

  隔板法就是我们假设有x个物品要分成n份，那么我们就要插n - 1个隔板，又因为可以满足为空的情况，
  那我们就先加进去n个物品，此时就有 x + n - 1个空，然后从中选择 n - 1个空。
  
  
  但是这样会超时，但是我们根据杨辉三角简单的判断一下就可以求出。
    
  当 $n <= m$ 时,答案是 ${{m + 1}\choose{n}} - {{m - 1}\choose{n}}$  
  当 $n > m$ 时， 答案是 ${m + n}\choose{n}$
  
 ```C++
 #include<bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 2e6 + 10, mod = 1e9 + 7;

i64 f[maxn], inv[maxn];
i64 ksm (i64 a, int b) {
    a %= mod;

    i64 res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

i64 C (int n, int m) {
    return f[n] * inv[m] % mod * inv[n - m] % mod;
}

int main()
{
    f[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = f[i - 1] * i % mod;
    inv[maxn - 1] = ksm(f[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;

    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d %d",&n, &m);
        if (n <= m) {
            printf("%lld\n", ((C(m + n, n) - C(m - 1, n)) % mod + mod) % mod );
        } else {
            printf("%lld\n", C(m + n, n));
        }
    }

    return 0;
}

 ```
 ```diff
 !    2022-10-27🤡
 ```
  
