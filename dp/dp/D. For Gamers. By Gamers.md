#  🌜[D. For Gamers. By Gamers.](https://codeforces.com/contest/1657/problem/D)


    纯纯大冤种！！没看到要保证所有的人都不死这句话！！！
    
    我们把按照公式推一下的话可以发现，其实他们的比较可以转为话 di*hi
    那么对于每一种士兵其都可以转化为 花费 c 元，能够实现 di*hi
    
    我们定义Max[c]代表花费c元能够获得最大的战斗力，这里的这个方法第一次见，感觉好神奇。

```C++
    for(int i = 1; i <= C; i++){
        for(int j = (i << 1) ; j <= C ; j += i){
            Max[j] = max(Max[j], Max[i] * j / i);
        }
    }
    for(int i = 1; i <= C ; i++) Max[i] = max(Max[i], Max[i-1]);
```
    同时需要注意的是最后一遍需要 Max[i] = max(Max[i], Max[i- 1])即之前的Max[i - 1]即为使用i - 1元取得的最大收益，
    但是可能Max[i]可能没有别更新到，或者是有点小，更新之后就是最大的了。
    
    
    而我们更新完Max数组之后，其实其所代表的收益也是递增的，那么我们就可以利用他求出达到要求所需的最小金额，又因为其需要大于
    所以这里使用upper_bound查找第一个比它大的。
    
AC代码：
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
    
    int n,C;   cin >> n >> C;
    vector<i64>Max(C + 1);
    
    for(int i = 1; i <= n ;i++){
        int c;  i64 d,h; 
        cin >> c >> d >> h;
        Max[c] = max(Max[c], d * h);
    }

    for(int i = 1; i <= C; i++){
        for(int j = (i << 1) ; j <= C ; j += i){
            Max[j] = max(Max[j], Max[i] * j / i);
        }
    }

    for(int i = 1; i <= C ; i++) Max[i] = max(Max[i], Max[i-1]);

    int m;  cin >> m;
    for(int i = 1; i <= m ;i++){

        i64 d,h;  cin >> d >> h;
        d = d * h;
        int p = upper_bound(Max.begin(), Max.end(), d) - Max.begin();

        if(p > C){
            cout << -1 <<  " ";
        } else {
            cout << p << " ";
        }
    }cout << endl;
    return 0;
}
```
```diff
!    2022-03-23🕌
```
    
