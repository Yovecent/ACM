# 🚡[E. Power Board](https://codeforces.com/contest/1646/problem/E)

    首先我们来定义一下，如果一个数不可以表示成x^a (a > 1)的形式，那么我们称其为强数，同时定义R(x):x,x^2,x^3....为x的集合。
    
    x例如：5,6,7...
    
    同时我们还需要证明一个性质，如果两个数x,y均为强数，那么他们的R()没有交集。
    
    假设x^a = y ^ b,那么x = y ^(b/a)
    同时又因为x是一个整数，那么y一定可以写成y = t^(k*a)即x = t^(k * b)，那么x就不是一个强数了。
    那么对于一个强数，我们就可以直接求他的R(x)的大小就可以了。
    我们考虑所有开头为x的幂次的行数，一共有k行，那么其实每一行的元素都可以写成x^(i * j), i : 1 -> k, j : 1 -> m。
    同时这个x^(i*j)的个数其实和x没有关系，之和k有关系。
    所有我们可以提前处理好对于每几行会有几种不同的元素就可以了，时间复杂度 m*log(n)
    
    然后我们就可以对于每一个n，如果他是强数就求一下他有几层，然后直接累加就行了，同时把他的幂次都标记一下防止重复。
    
    
    还有不知道为啥使用换底公式为因为精度导致wa,直接使用log2()的函数就没事。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int info[30];
bool vis[20000010],st[1000010];

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    i64 n;
    int m;
    cin >> n >> m;

    for(int i = 1; i <= log2(n) ; i++){
        info[i] = info[i - 1];
        for(int j = 1; j <= m ; j++){
            if(!vis[i * j]){
                vis[i * j] = 1;
                info[i]++;
            }
        }
    }

    i64 ans = 1;
    for(int i = 2; i <= n ; i++){

        if(st[i]) continue;
        i64 x = i;
        int cnt = 0;
        while(x <= n){
            cnt++;
            st[x] = true;
            x *= i;
        }
        ans += info[cnt];
    }

    cout << ans << endl;
    return 0;
}
```
```diff
!      ⚖️2022-03-05
```
