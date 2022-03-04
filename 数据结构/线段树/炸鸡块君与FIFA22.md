##  🏺[炸鸡块君与FIFA22](https://ac.nowcoder.com/acm/contest/23106/B)

    线段树真是个好东西！！！
    首先这道题时根据是否能被3整除来看会不会有存档，那么其实我们就可以将得分都模3,此时状态也就
    只剩下了3种。
    这里我们就要用到多维线段树，因为我们在某一处L时，其此时的得分我们并不知道，所以只需要针对一位将3种情况
    都更新一下就可以了。
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 2e5 + 10;

int nxt[5][300];
string s;

struct segmentTree{

    int info[maxn << 2][3];

    void pushup(int p,int l,int r){
        for(int i = 0 ; i < 3 ; i++){

            info[p][i] = info[p << 1][i] + info[p << 1| 1][((i + info[p << 1][i]) % 3 + 3) % 3];
        }
    }
    void build(int p,int l,int r){

        if(l == r){

            for(int i = 0 ; i < 3 ; i++){
                info[p][i] = nxt[i][s[l - 1]];
            }
            return;
        }

        int mid = l + r >> 1;
        build(p << 1, l , mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p,l,r);
    }
    int query(int p,int l,int r,int L,int R,int k){

        if(l >= L && r <= R){

            return info[p][k];
        }

        int res = 0,ans = 0;
        int mid = l + r >> 1;
        if(L <= mid) ans = query(p << 1, l, mid, L, R, k);
        if(R > mid)  ans += query(p << 1 | 1, mid + 1, r, L, R, ((k + ans) % 3 + 3) % 3);
        return ans;
    }
}tree;

void init(){

    nxt[0]['W'] = 1,nxt[0]['L'] = 0, nxt[0]['D'] = 0;
    nxt[1]['W'] = 1,nxt[1]['L'] = -1,nxt[1]['D'] = 0;
    nxt[2]['W'] = 1,nxt[2]['L'] = -1,nxt[2]['D'] = 0;
    
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    init();
    int n,q;
    cin >> n >> q;
    cin >> s;
    
    tree.build(1,1,n);
    while(q--){

        int l,r,k;
        cin >> l >> r >> k;
        cout << k + tree.query(1,1,n,l,r,k % 3) << endl;
    }

    return 0;
    
}
```

##  🥣[进制](https://ac.nowcoder.com/acm/contest/23479/B)

    这两道题其实基本上都是类似的，均使用了多维的线段树。
    而对于本题，我们可以新开一个Max,len数组，记录线段的长度以及其中的最大值。
    然后对于区间合并，我们可以知道，将p << 1 合并 p << 1 | 1时，即将p << 1中的元素进制提高
    进制 ^ len[p << 1 | 1]，就可以了。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;

string s;
int rs;
i64 res,ti[20][maxn];
struct segmentTree{
    
    i64 info[maxn << 2][20];
    int Max[maxn << 2],len[maxn << 2];

    void pushup(int p){
        for(int i = 2; i <= 10 ; i++){
            info[p][i] = (info[p << 1][i] * ti[i][len[p << 1 | 1]] % mod +  info[p << 1 | 1][i]) % mod;
        }
        Max[p] = max(Max[p << 1],Max[p << 1 | 1]);
        len[p] = len[p << 1] + len[p << 1 | 1];
    }
    void build(int p,int l,int r){

        if(l == r){
            for(int i  = 2 ; i <= 10 ; i++){
                info[p][i] = s[l - 1] - '0';
            }
            Max[p] = s[l - 1] - '0';
            len[p] = 1;
            return ;
        }

        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int p,int l,int r,int x,int val){
        if(l == r){
            for(int i = 2; i <= 10;  i++){
                info[p][i] = val;
            }
            Max[p] = val;
            return;
        }
        int mid = l + r >> 1;
        if(x <= mid) update(p << 1, l, mid, x, val);
        else         update(p << 1 | 1, mid + 1, r, x, val);
        pushup(p);
    }
    void get_Max(int p,int l,int r,int L,int R){
        if(l >= L && r <= R){

            rs = max(rs ,Max[p]);
            return;
        }
        int mid = l + r >> 1;
        if(L <= mid) get_Max(p << 1, l , mid , L ,R);
        if(R > mid)  get_Max(p << 1 | 1,mid + 1, r , L ,R);

    }
    void query(int p,int l,int r,int L,int R){
        if(l >= L && r <= R){
            res += info[p][rs] * ti[rs][R - r] % mod;
            res %= mod;
            return;
        }
        int mid = l + r >> 1;
        if(L <= mid) query(p << 1, l ,mid , L ,R);
        if(R > mid) query(p << 1 | 1, mid + 1, r ,L ,R);
    }
}tree;
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);
    
    int n,q;
    cin >> n >> q;
    cin >> s;
    for(int i = 2 ; i <= 10 ; i++) ti[i][0] = 1;
    for(int i = 2 ; i <= 10 ; i++){
        for(int j = 1; j <= n ; j++){
            ti[i][j] = ti[i][j - 1] * i % mod;
        }
    }

    tree.build(1,1,n);
    while(q--){

        int opt,x,y;
        cin >> opt >> x >> y;
        if(opt == 1){

            tree.update(1,1,n,x,y);
        } else {
            
            rs = res = 0;
            tree.get_Max(1,1,n,x,y);
            rs++;
            tree.query(1,1,n,x,y);
            cout << res << endl;
        }
    }

    return 0;
}
```

```diff
!     🛺2022-03-04
```
