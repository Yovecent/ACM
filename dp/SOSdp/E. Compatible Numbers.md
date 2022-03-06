#  🥓[E. Compatible Numbers](https://codeforces.com/contest/165/problem/E)


    感觉可能学习了SOSdp会对于位运算有了更深的认识。
    
    这道题中的定义是 a & b == 0。
    那么我们求一下a的反可以发现，如果a & b == 0，那么 b一定是 ^a的子集。
    
    例如: a  = 10010
          ^a = 01101
          b  = 01100
    因为a & b等于0,说明a为1的地方b一定为0，a为0的地方b可以为1，
    那么反过来就是说   ^a为0的地方b一定为0，a为1的地方b可以为1。
    WOW！这不就是子集的概念吗？
    
    所以我们只需要求一下F，然后查询的是 ^a就可以了。
    
    同时我们这里不让求的a[i]的求和，而是随便找一个就可以了。
    那么令F[a[i]] = a[i]。
    考虑一下F的定义就可以知道，即使让所有a[i] = i了。
    那么对于i属于mask,那么就可以让F[mask]存下i，也就是我们一开始拥有的数了。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = (1 << 22);

int F[maxn],a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 0 ; i < n ; i++){

        int x;
        cin >> x;
        a[i] = x;
        F[x] = x;
    }
    for(int i = 0 ; i < 22 ; i++){
        for(int mask = 0 ; mask < maxn ; mask++){

            if(F[mask]) continue;
            if(mask & (1 << i)){
                F[mask] = F[mask ^ (1 << i)];
            }
        }
    }

    int s = maxn - 1;
    for(int i = 0 ; i < n ; i++){
        if(F[s ^ a[i]]) cout << F[s ^ a[i]] << " ";
        else         cout << -1 << " ";
    }
    cout << endl;
    return 0;
}
```

```diff
!     🎨2022-03-06
```
