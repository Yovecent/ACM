# ✈️[D. Binary Spiders](https://codeforces.com/problemset/problem/1625/D)

    之前写过一道类似的，这里依然是应用了前缀相同的思想。
     
    设k的最大的1的位置是x。
    我们把每一个数都拆分成30位的二进制形式。
    如果在x之前两个数有某一位上不同，那就一定比k大！
    我们就可以从29 - (k+1)位不断地分组，那分到第k位时，只有前缀相同的才会在一组，
    而我们只要任意的从两个组中跳出来两个数，他们两个的异或结果一定大于k。
    这里我们不用vector不断地分组来计算了。
    直接把 [val >>  (x + 1)] 相同的存在一个map里面就相当于分组了。
    
    
    然后就是接下来k位的比较，其实每一组内要么我们选一个，要么最多只能选两个，因为我们一旦选择了
    3个，那么就必定会有两个这一位异或是0，也就 < k了。
    所以我们需要做的就是对每一组查询出最大的两个异或的值。
    
    
    这里的方法是字典树，每次插入和查询的时间复杂度为O(30)即为位数。
    因为我们查询时，都想要往反方向走，如果没有就按当前位相同的走。
```C++
void build(int x){
    int p = 0;
    for(int i = 29 ; i >= 0 ; i--){
        int k = x >> i & 1;
        if(!tr[p][k]){
            tr[p][k] = ++ tot;
        }
        p = tr[p][k];
    }
}
int find(int x){
    int res = 0, p = 0;
    for(int i = 29 ; i >= 0 ; i--){
        int k = x >> i & 1;
        if(tr[p][!k]){
            p = tr[p][!k];
            if(!k) res += (1 << i);
        } else {
            p = tr[p][k];
            if(k) res += (1 << i);
        }
    }
    return res;
}
```
    还有需要注意的memset函数， memset(name, val, sizeof (type) * n * m)
    这是清空二维数组的格式。记得要加(type)因为不同变量的位数不同。
    
AC代码：
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 3e5 + 10;

map<int,vector<int>> info;
map<int,int>id;
int tot,tr[maxn * 30][2];
vector<int>v;

void build(int x){
    int p = 0;
    for(int i = 29 ; i >= 0 ; i--){
        int k = x >> i & 1;
        if(!tr[p][k]){
            tr[p][k] = ++ tot;
        }
        p = tr[p][k];
    }
}
int find(int x){
    int res = 0, p = 0;
    for(int i = 29 ; i >= 0 ; i--){
        int k = x >> i & 1;
        if(tr[p][!k]){
            p = tr[p][!k];
            if(!k) res += (1 << i);
        } else {
            p = tr[p][k];
            if(k) res += (1 << i);
        }
    }
    return res;
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int n, k, opt;
    cin >> n >> k;
    if(!k){
        cout << n << endl;
        for(int i = 1; i <= n ;i++) cout << i << " ";
        return 0;
    }
    bitset<30> s = k;
    for(int i = 30 ; i >= 0 ; i--){
        if(s[i]){
            opt = i;
            break;
        }
    }
    opt ++;

    for(int i = 1, x;  i <= n ;i++){
        cin >> x;
        id[x] = i;
        info[x >> opt].push_back(x);
    }

    for(auto [now, mask] : info){
        memset(tr, 0 , sizeof (int) * (tot + 1) * 2);
        tot = 0;
        bool ok = false;
        for(auto val : mask){
            int res = find(val);
            if((res ^ val) >= k){
                v.push_back(id[val]);
                v.push_back(id[res]);
                ok = true;
                break;
            }
            build(val);
        }
        if(!ok) v.push_back(id[mask[0]]);
    }
    if(v.size() > 1){
        cout << v.size() << endl;
        for(auto x : v)  cout << x << " ";
    } else {
        cout << -1 << endl;
    }

    return 0;
}
```

```diff
!   🍻2022-03-20
```
