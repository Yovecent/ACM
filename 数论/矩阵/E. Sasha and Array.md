# 🥓[E. Sasha and Array](https://codeforces.com/problemset/problem/719/E)

    这道题当时推的其实有点乱，虽然说能写，但是最后还是TLE了。
    
    本来想的是对每一个点都设为线段树的单点，然后懒标记记录的是这个点还要再进行几次递推公式，
    其实感觉和最终的矩阵版本类似，但是时间被卡住了。
    
    后来想想，其实用矩阵更好些，方便且高效。

+   线段树维护矩阵

    
    我们将每一个点都定义为一个(2×2)的矩阵, c[0][1]处的值记录为当前点的值，c[0][0]记录为当前的点
    在斐波那契的上一个值。
    而我们完全可用线段树，且意义为[L,R]区间的和，定义同上。并且我们的懒标记也定义为矩阵，即记录递推的次数，这里
    让其空时变为单位矩阵，直接让其乘上递推公式的进行递推完的的矩阵，同理更新info矩阵时也是让他乘上懒标记的矩阵。
    
    这样想想其实和基本的线段树没有什么区别了。
    
    
    这一次也是深刻理解了一下懒标记的含义：
    我们需要保证，懒标记已经更新了当前节点，并且还没有去更新下面的点，所以如果我们再次去更新到一个已经有懒标记的
    区间，就需要在之前的基础上再去更新，并且更新懒标记。

懒标记伪代码：
```C++
  void update(int p,int l,int r,int L,int R,int x){
        if(l >= L && r <= R){
              lazy[p]更新
              info[p]更新
              return;
        }
        pushdown(p)
        l -----;
        r -----;
        pushup(p);//这里需要更新一下，因为还没有计算好此时的真实值
  }
  void query(int p,int l,int r,int L,int R){
        if(l >= L && r <= R){
              return info[p];
        }
        pushdown(p);
        l ----;
        r ----;
        //这里不用pushup，因为如果到这里，就代表已经算过整块的了，只是把需要更新的内容传下去
  }
```

AC代码：
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;
const int maxn = 1e5 + 10, mod = 1e9 + 7;

i64 a[maxn];
struct Mat{

    i64 c[2][2] =
        {
            {0, 0},
            {0, 0}
        };
    void one(int x){
        for(int i = 0 ; i < 2 ; i++){
            for(int j = 0 ; j < 2 ; j++){
                c[i][j] = i == j ? x : 0;
            }
        }
    }
    bool operator == (Mat b){
        for(int i = 0 ; i < 2; i++){
            for(int j = 0 ;  j <  2; j++){
                if(c[i][j] != b.c[i][j]) return false;
            }
        }
        return true;
    }
}base, ans, res, one;
Mat operator + (Mat A, Mat B){
    Mat C;
    for(int i = 0 ; i < 2; i ++){
        for(int j = 0 ; j < 2; j++){
            C.c[i][j] = (A.c[i][j] + B.c[i][j]) % mod;    
        }
    }
    return C;
}
Mat operator *(Mat A, Mat B){
    Mat C;
    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            for(int k = 0 ; k < 2 ; k++){
                C.c[i][j] = (C.c[i][j] + A.c[i][k] * B.c[k][j] % mod) % mod;
            }
        }
    }
    return C;
}
Mat ksm(Mat a,i64 b){

    Mat res;
    res.c[0][0] = 1,res.c[1][1] = 1;
    while(b){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
struct SegmentTree{

    Mat info[maxn << 2],lazy[maxn << 2];

    void pushup(int p){

        info[p] = info[p << 1] + info[p << 1 | 1];
    }
    void pushdown(int p){

        if(lazy[p] == one) return;
        lazy[p << 1] = lazy[p << 1] * lazy[p];

        lazy[p << 1 | 1] = lazy[p << 1 | 1] * lazy[p];

        info[p << 1] = info[p << 1] * lazy[p];

        info[p << 1 | 1] = info[p << 1 | 1] * lazy[p];

        lazy[p].one(1);
    }
    void build(int p,int l,int r){
        lazy[p].one(1);
        if(l == r){
            if(a[l] == 1){
                info[p].c[0][1] = 1;
            } else if (a[l] == 2) {
                info[p].c[0][0] = info[p].c[0][1] = 1;
            } else {
                info[p] = res * ksm(base , a[l] - 2);
            }
            return ;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int p,int l,int r, int L, int R,Mat x){
        if(l >= L && r <= R){
            info[p] = info[p] * x;
            lazy[p] = lazy[p] * x;
            return;
        }
        pushdown(p);
        int mid = l + r >> 1;
        if(L <= mid) update(p << 1, l, mid, L, R, x);
        if(R > mid)  update(p << 1 | 1, mid + 1, r, L, R, x);
        pushup(p);
    }
    void query(int p,int l,int r,int L,int R){
        if(l >= L && r <= R){ 
            ans = ans + info[p];
            return ;
        } 
        pushdown(p);
        int mid = l + r >> 1;
        if(L <= mid) query(p << 1, l, mid, L, R);
        if(R > mid)  query(p << 1 | 1, mid + 1, r, L, R);
    }
}tree;
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    base.c[0][1] = 1,base.c[1][0] = 1,base.c[1][1] = 1;
    res.c[0][0] = 1,res.c[0][1] = 1;
    one.one(1);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n ; i++) cin >> a[i];
    tree.build(1, 1, n);

    while(q--){

        int opt, l, r, val;
        cin >> opt;

        if (opt == 1) {

            cin >> l >> r >> val;
            tree.update(1, 1, n, l, r, ksm(base, val));
        } else {

            cin >> l >> r;
            ans.one(0);
            tree.query(1, 1, n, l, r);
            cout << ans.c[0][1] << endl;
        }
    }
    return 0;
}
```
```diff
!    2022-03-23🛀
```
