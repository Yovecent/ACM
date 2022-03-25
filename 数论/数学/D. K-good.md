#  ❔[D. K-good](https://codeforces.com/contest/1656/problem/D)


    推公式推了半天，答案竟然这么严谨又巧妙。
    
    
    我们可以简单地推出的是：
    n = ((k + 1) * k) / 2 + m * k  
    也就是说他是关于一个k的公式，但是推了很久，因为有两个未知数，啥也推不出来QAQ
    
    (1) k为偶数
    我们先来考虑2 * n
    2n = (k + 1) * k + m * k
    可以发现的是，(2n % k == 0)也就是说，k是2n的一个因子
    
    因为k为偶数，所以(k + 1) * k / 2一定是一个奇数，那就是说明，k一定是不n的因子。
    那么我们的任务就是找到一个因子x，其是2n的因子，但不是n的因子。
    
    那么我们考虑一个最简单的因子，因为每一个数都可以话为质数的质数乘积形式，
    也就是说n = 2^k1*3^k2....
    那么我们令K1 = 2^(k1 + 1)
    那么其一定满足是2n的因子而不是n的因子。
    
    此时只要保证((K1 + 1) * K1) / 2 <= n 就可以了，因为不够的话我们可以用mK取补足。
    
    (2)k为奇数，如果(1)不满足的话一定是因为((K1 + 1) * K1) / 2 > n-------(*)
    
    对于这里，其实答案就是K2 = 2 * n / K1
    
    由(*)可以推出  ((K1 + 1) * K1) > 2 * n
                          (K1 + 1) > K2
    
    又因为K1是偶数，K2是奇数，所以：
                         K2 <= K1 - 1
    所以:
          (K2 + 1) * K2 / 2 <= K1 * K2 / 2 = n
    
    由此我们得出一个结论:
    答案一定在K1,K2中产生。
    所以我们只需输出其中较小的那个。
    
    但是特例是当n 是2 的整数倍时，K1 = 2n, K2 = 1
    此时是没有答案的，所以就输出-1
    
    
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;


int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;  cin >> t;
    while(t--){

        i64 n;  cin >> n;
        i64 k = 1;
        while(n % 2 == 0){
            n /= 2;
            k *= 2;
        }
        if(n == 1){
            cout << "-1" << endl;
        } else {
            cout << min(n, 2 * k) << endl;
        }
    }

    return 0;
}
```
```diff
!    2022-03-25🐡
```
