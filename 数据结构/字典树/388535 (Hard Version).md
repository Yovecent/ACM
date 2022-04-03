#  🔋[388535 (Hard Version)](https://codeforces.com/contest/1658/problem/D2)

    
    
    一道好题呀！！！
    
  首先我们需要知道，对于不同的数异或上同一个数，所得的数一定也都不相同。
  
  我们的a数组是通过将 l, r内的数异或上x得到的，那么也就说明了其中一定有一个数是a[i] = l ^ x得到的，
  那么我们我们遍历每一个数，让a[i] ^ l ,就一定会出现 x 。
+  但出现了x有什么用呢？

   这就用到了之前字典树的用处：求一个数与数组中的数的异或最大值或最小值。
   我们如果让这个数去和我们的a[]数组求取最大，最小的异或值，如果其恰好等于l,r那也就是说我们让x
   去异或上a的数组中的每一个数都会落在[l,r]内，同时每一个数异或上x都是不相等的，所以他们就一定是
   [l,r]的全部数。
   
   
   那么我们就将每一个数插入到字典树中，然后求最大最小值，再与l,r比较就可以了。
   
   同时求取最大最小值，应该从高位向低位，因为这样贪心才能使得值最大与最小。
   
   
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int cnt;
struct Trie{

    int tr[1 << 17][2];
    void init(){
        memset(tr, 0, sizeof(int) * (cnt + 1) * 2);//初始化小技巧
        cnt = 0;
    }
    void insert(int val){
        int p = 0;
        for(int i = 16; i >= 0 ; i--){
            int u = val >> i & 1;
            if(!tr[p][u]){
                tr[p][u] = ++cnt;
            }
            p = tr[p][u];
        }
    }
    int Max(int val){
        int p = 0, sum = 0;
        for(int i = 16; i >= 0 ; i--){
            int u = val >> i & 1;
            if(tr[p][!u]){
                sum += 1 << i;
                p = tr[p][!u];
            } else {
                p = tr[p][u];
            }
        }
        return sum;
    }
    int Min(int val){
        int p = 0, sum = 0;
        for(int i = 16; i >= 0 ; i--){
            int u = val >> i & 1;
            if(tr[p][u]){
                p = tr[p][u];
            } else {
                sum += 1 << i;
                p = tr[p][!u];
            }
        }
        return sum;
    }

}tree;
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;  cin >> t;
    while(t--){
        tree.init();
        int l, r;  cin >> l >> r;
        vector<int>a(r - l + 1);
        for(int &x : a)  cin >> x,tree.insert(x);

        for(auto x : a){
            int io = x ^ l;
            int Max = tree.Max(io);
            int Min = tree.Min(io);
            if(Max == r && Min == l){
                cout << io << endl;
                break;
            } 
        }
    }

    return 0;
}
```

```diff
!   2022-04-03🐈‍
```
