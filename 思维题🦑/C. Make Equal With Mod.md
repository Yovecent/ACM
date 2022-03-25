#  😢[C. Make Equal With Mod](https://codeforces.com/contest/1656/problem/C)


    单纯的一道思维题，真是想不出来。。。。。
    
    首先这道题一开始都是往怎么模一两次让他出来答案，但是发现都无济于事。
    
    这里其实就告诉了一个很重要的地方，小的不行就往大的想。
    
    因为对于取模操作，我们如果用一个数组中出现的最大数去模所有的数的话，就只会对最大值的地方出现影响。
    而对其他小的数没有影响，那么也就是说，我们每次都让此时数组中最大的数去模的话，就会一步一步地把他们
    变成0(除了1)。
    
    对于这种办法，如果数组中没有1的话，那就说明我们是可以变成的。
    
    
    如果数组中出现1的话，那么要想让他们都变成相同的，就都让他们变成1，而我们此时最大值为Max，那么我们只需摸上Max - 1，
    就可以出来1，而如果说数组中出现两个相邻的数，那就一定不会成立，因为我们不管让他俩摸上几最后都是会差一，最终就会出现
    0，1而无法成立。
    
ACcode
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

        int n;  cin >> n;
        map<int,bool>vis;
        bool ok = false;
        for(int i = 0 ; i < n ;i++){
            int x;  cin >> x;
            if(vis[x + 1] || vis[x - 1]){
                ok = true;
            }
            vis[x] = true;
        }
        if(!vis[1] || !ok){
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
```
```diff
!     2022-03-25🛎️
```
    
