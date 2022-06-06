<span id="jump0"></span>

## title
  ### 🥛Set or Decrease
  ### 🦑[P2824 [HEOI2016/TJOI2016]排序](#jump1)
<br>
<br>
<br>

#  🥛[Set or Decrease](https://www.luogu.com.cn/problem/CF1622C)

+   所以说二分是useful algorithm呀！！！

    首先贪心的去想，我们肯定是让最小的值去执行第一个操作，然后再让大于他的的数执行第二个操作。
    因为对于大于他的数，我们执行第二个操作一定不会坏于第一个操作，因为执行第一个操作至少会
    让他减少一个。
    
    
    所以我们的计算答案  = 操作一 + 操作二
    
    而我们知道，我们需要做的就是让最小值执行操作一，然后从最大值到最小值去执行操作二，尽管我们不知道
    在那种情况下会最小，以及怎么变一下会更优化，但是只要我们定一了一个答案，我们就一定用O(n)的复杂度找出来。
    这样他还是具有单调性的，即步骤越多越有可能做到。
    对于每一次的mid，我们从后往前，假设对这几个执行操作二，那么我们剩下的操作就去给最小值，计算出一个答案比一下
    是否成立了。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

i64 a[200010], k;
int  n; 
bool check(i64 mid){

    i64 sum = 0;
    for(int i = 0 ; i <= min(mid, 1ll * (n - 1)) ; i++){
        i64 cnt = mid - i;
        sum += a[i];
        if(sum + cnt - (a[n] - cnt) * i >= k) return true;
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;  cin >> t;
    while(t--){

        cin >> n >> k;
        i64 sum = 0;
        for(int i =  1 ; i <= n ; i++)  cin >> a[i], sum += a[i];
        sort(a + 1, a + n + 1,[](i64 x,i64 y){
            return x > y;
        });
        k = sum - k;

        i64 l = 0, r = a[n] + n - 1;
        while(l < r){ 

            int mid = l + r - 1 >> 1;
            if(check(mid)){
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        cout << r << endl;
    }
}
```
```diff
!   2022-04-02 🐤
```
<br>
<br>
<br>

[返回](#jump0)

<span id="jump1"></span>

#   [🦑[P2824 [HEOI2016/TJOI2016]排序]](https://www.luogu.com.cn/problem/P2824)

    
    真的是被二分的思想给秀到了，真是太useful了！！！
    因为这道题是让我们去找到排序之后位置q上的数，所以其是我们可以把这些数分为两种
    小于x的， 等于x的， 大于x的
    所以我们的任务就是将这三种数在不断地排序
    
    
    因为我们如果只看重排序的话很难做出来，我们需要借助点数据结构来协助，所以我们需要将排序的步骤
    转化为另外一种形式。
   
+   🐳如果我们只有01两种数字，对这个区间进行排序的话有什么简便的方法呢？
    
    因为只有01，所以如果是升序的话，我们只需要将所有的0排在最左边，1排在最右边，
    反之就交换一下01的位置。这个过程其是就是将排序的步骤转化为了区间修改，我们只需要知道
    这个区间的长度，以及区间中1的个数，然后就根据升序还是降序进行区间修改就可以了。
    
    
    我们可以使用二分，来查找出正确的那个数
    那么我们可以将大于等于x的数设为1，小于x的数设为0，然后进行线段树修改，这个位置最后是1就说明可以l = mid，否则
    r = mid - 1
    
    为什么使用二分正确呢？
    
    我们设想一下如果这个位置是1的话那就说明这个现在这个位置上的数是在大小区间为[mid, n]的，
    如果是0的话那就说明是在[1, mid]，又因为我们维护的l,r
    所以如果这个位置是1，那就说明答案在[mid, r]
    如果这个位置是0，那就说明答案在[l, mid - 1]
    
    所以一道十分复杂的题目就被我们简单化了，真的太神奇了！！！
    
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 1e5 + 10;

int a[maxn], b[maxn];

struct SegmentTree{

    int info[maxn << 2], lazy[maxn << 2];

    void pushup (int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }
    void pushdown (int p, int l, int mid, int r) {
        if (lazy[p] != -1) {
            lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
            info[p << 1] = lazy[p] * (mid - l + 1);
            info[p << 1 | 1] = lazy[p] * (r - mid);
            lazy[p] = -1;
        }
    }
    void build (int p, int l, int r) {
        lazy[p] = -1;
        if (l == r) {
            info[p] = b[l];
            return ;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    int query (int p, int l, int r, int L, int R) {

        if (l >= L && r <= R) {
            return info[p];
        }
        
        int mid = l + r >> 1, ans = 0;
        pushdown(p, l, mid, r);
        if (L <= mid) ans += query(p << 1, l, mid, L, R);
        if (R > mid)  ans += query(p << 1 | 1, mid + 1, r, L, R);
        return ans;
    }

    void update (int p, int l, int r, int L, int R, int k) {
        if(L > R) return;
        if (l >= L && r <= R) {
            info[p] = (r - l + 1) * k;
            lazy[p] = k;
            return;
        }
        int mid = l + r >> 1;
        pushdown(p, l, mid, r);
        if(L <= mid) update(p << 1, l, mid, L, R, k);
        if(R > mid)  update(p << 1 | 1, mid + 1, r, L, R, k);
        pushup(p);
    }

}tree;

struct node{
    int op, l, r;
};
int n;

bool judge(int x, vector<node> v, int p){

    for(int i = 1; i <= n ; i++) b[i] = (a[i] >= x);

    tree.build(1, 1, n);

    for (auto [op, l, r] : v) {
        int cnt = tree.query(1, 1, n, l, r);
        if (op) {
            tree.update(1, 1, n, l, l + cnt - 1, 1);
            tree.update(1, 1, n, l + cnt, r, 0);
        } else {
            tree.update(1, 1, n, l, r - cnt, 0);
            tree.update(1, 1, n, r - cnt + 1, r, 1);
        }
    }

    return (tree.query(1, 1, n, p, p) == 1);
}
int main() {

    int q; 
    scanf("%d %d",&n,&q);
    for (int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }
    
    vector<node>v(q);
    for (int i = 0; i < q; i++) {
        int op, l, r;  
        scanf("%d %d %d",&op,&l,&r);
        v[i] = {op, l, r};
    }

    int pos;
    scanf("%d",&pos);

    int l = 1, r = n;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if(judge(mid, v, pos)){
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    printf("%d\n",l);


    return 0;
}
```
```diff
!    🌩️2022-06-06
```
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
