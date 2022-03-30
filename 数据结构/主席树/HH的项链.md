#  🗳️[HH的项链](https://www.luogu.com.cn/problem/P1972)
    
    
    这道题之前的树状数组的方法和这个差不多，但是用主席树感觉更加巧妙。
    
    这里的区间即为按照值来划分，节点含义为一个数的下一个离他最近的相同的数的位置。
    
    这里我们利用了前缀和的思想。
    [1 ~ (L - 1)] [L  ~  R]
    我们想要统计出L ~ R内的数，那么我们只需要统计这里面nxt大于R的数就可以了，即在[L , R]中每一个数最后一次出现的
    才会有贡献，这样可以保证只记上一次。
    而在1 ~ (L - 1)中 nxt > R那么一定是在[L, R]内也没有出现过的，所以他也被记录在了1 - R内。
    所以用 R时的树减去L-1时的的树就是L - R区间内的点构成的树，那么我们统计 > R的节点的个数就可以了。
    
    
```C++
#include <bits/stdc++.h>

#define L(x)  (tr[x].l)
#define R(x)  (tr[x].r)
#define endl "\n"
using namespace std;
using i64 = long long;
const int maxn = 1e6 + 10;

int n, q, cnt, pos[maxn], a[maxn], vis[maxn];

struct Chairman_Tree{
    int root[maxn];
    struct node{
        int w, l, r;
    }tr[maxn * 20];

    void update(int &now, int l, int r, int x){

        tr[++cnt] = tr[now], now = cnt;
        tr[now].w++;
        if(l == r) return;
        int mid = l + r >> 1;
        if(x <= mid) update(L(now), l, mid, x);
        else         update(R(now), mid + 1, r, x);
    }

    int query(int i, int j, int l,int r,int x){

        if(l == r) return tr[j].w - tr[i].w;
        int mid = l + r >> 1;
        if(x > mid) return query(R(i), R(j), mid + 1, r, x);
        else        return query(L(i), L(j), l, mid, x) + tr[R(j)].w - tr[R(i)].w;
    }
}tree;

int main() 
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;  cin >> n;
    for(int i = 1; i <= n ; i++)  cin >> a[i];
    for(int i = n ; i >= 1; i--){
        if(!vis[a[i]]){
            pos[i] = n + 1;
        } else {
            pos[i] = vis[a[i]];
        }
        vis[a[i]] = i;
    }
    
    for(int i = 1; i <= n ; i++){
        tree.root[i] = tree.root[i - 1];
        tree.update(tree.root[i], 1, n + 1, pos[i]);
    }

    int q;  cin >> q;
    while(q--){
        int l, r;  cin >> l >> r;
        cout << tree.query(tree.root[l - 1], tree.root[r], 1, n + 1, r + 1) << endl;
    }

    return 0;
}
```
```diff
!   2022-03-30🍀
```
