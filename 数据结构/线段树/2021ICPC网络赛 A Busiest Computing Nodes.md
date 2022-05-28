<span id="jump0"></span>
<br>

## [2021ICPC网络赛 A Busiest Computing Nodes](#jump1)
## [P1382 楼房](#jump2)
## [Operations on a Matrix](#jump3)
<br>
<br>
<br> 

<span id="jump1"><span>
   
    
# 💥线段树真是个好东西  
🐪这道题考查的是线段树和二分的结合  

<span id="jump1"><span>
    
    首先他要求我们按照一个圈来找有咩有一个空闲的机器，一开始我是想的用倍增的方法去写，先从这个机器的右边往左跑，能
    跑则跑，找到一个里当前机器最近的，如果没有，就从这个机器的左边一个机器往左跑，这样想似乎是对的，但是问题是，他并
    不是一个成序的一个序列，也就是说并不是你找到了一个合法的那么离他近的都合法。  
 
```diff
! 但是用线段数就恰好满足了这个需求，我们在利用二分，如果当前左区间内最小值比到达时间小于等于，那么我们就可以把r设为mid，
! 否则l设为mid+1，并且线段树的操作时间都是log级别的

+ 还有一个需要注意的点是，ar是到达时间，en是操作时间，那么他完成的时间应该是ar+en-1,所以就是说下一个任务到达时间 >= ar+en都是可以的

+ 所以我们这道题的最坏时间复杂度是 n(logn)^2
```

```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 1e5+10;
const int INF= 0x3f3f3f3f;
int tr[maxn<<2],cnt[maxn],n,K;

void update(int p,int l,int r,int x,int val){

    if(l == r){
        tr[p]=val;return;
    }
    int mid=l+r>>1;
    if(x <= mid) update(p<<1,l,mid,x,val);
    else         update(p<<1|1,mid+1,r,x,val);
    tr[p]=min(tr[p<<1],tr[p<<1|1]);
}

int query(int p,int l,int r,int L,int R){

    if(l >= L && r <= R){
        return tr[p];
    }
    int mid=l+r>>1,res=INF;
    if(L <= mid)   res=min(res,query(p<<1,l,mid,L,R));
    if(R > mid)    res=min(res,query(p<<1|1,mid+1,r,L,R));
    return res;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    memset(tr,0,sizeof tr);
    scanf("%d %d",&K,&n);
    for(int i = 0 ; i < n ; i++){
        int k=i%K+1;int ar,en;scanf("%d%d",&ar,&en);
        if(tr[1] > ar){
            continue;
        }
        int l,r;
        if(query(1,1,K,k,K) <= ar) l=k,r=K;
        else                      l=1,r=k-1;
        while(l<r){
            int mid=l+r-1>>1;
            if(query(1,1,K,l,mid) <= ar){
                r=mid;
            }
            else  l=mid+1;
        }
        update(1,1,K,l,ar+en);
        cnt[l]++;
    }
    int Max=0;
    for(int i = 1; i <= n ; i++) Max=max(Max,cnt[i]);
    bool f=true;
    for(int i = 1 ; i <= n ; i++){
        if(Max == cnt[i]){
            if(f)  printf("%d",i-1),f=false;
            else   printf(" %d",i-1);
        }
    }
    return 0;
}
```

<br>
<br>
<br>

<span id="jump2"> </span>
    
# [P1382 楼房](https://www.luogu.com.cn/problem/P1382?contestId=68990)
![image](https://user-images.githubusercontent.com/92497177/167288058-6d5509df-fa1f-43e7-bcb3-42c58b097913.png)

    
 ###  方法一：扫描线
    
    这道题属于是扫描线的模板题了，但是我还是第一次见QAQ
    
    首先对于扫描线需要记住对于入边和出边的考虑。
    
    这里一条出边会把加进去的入边删除，所以存在的边一定是个左边，并且其右边还未出现。
    在这道题里面，我们考虑入边也就是左边，怎么会对答案有贡献。
    那一定是高于当前所有的边，不然就相当于左边被吞噬了。
    那么我们再考虑右边，这个比较难。
    
    直接说结论：与其高相同的边只有一条。
    我们先考虑如果说有两条左边和他高相同，那么我们我们一定可以将其再延伸，也就是说这个边会被吞噬。
    如果有比他高的边出现时，那我们想一下那就是说其上面一定还有边那也会被吞噬。
    
    所以我们动态的加左边，判断是否有点，再加入右边时判断完之后再将其对应的左边删除。
    
    这里我们只需要其高度而对下标没有什么要求，所以用了 multiset
```C++
    #include <bits/stdc++.h>

using namespace std;
using i64 = long long;

struct line{
	
	int x, h, id;
	friend bool operator <(line a, line b){
		
		if(a.x != b.x)  return a.x < b.x;
		if(a.id != b.id) return a.id < b.id;
		if(a.id == 0) return a.h > b.h;
		if(a.id == 1) return a.h < b.h;
	}
};
int main()
{	
	int n;  scanf("%d",&n);
	vector<line> p(n << 1);
	int cnt = 0;
	for(int i = 0 ; i < n ; i++){
		int h, r, l;  scanf("%d %d %d",&h,&l,&r);
		p[cnt++] = {l, h, 0};
		p[cnt++] = {r, h, 1};
	}
	sort(p.begin(), p.end());
	
	multiset<int>s;  s.insert(0);
	vector<pair<int,int> >v;
	for(int i = 0 ; i < p.size() ; i++){
		int Max = *s.rbegin();
		if(p[i].id == 0){
			if(p[i].h > Max) {
				v.push_back({p[i].x, Max});
				v.push_back({p[i].x, p[i].h});
			}
			s.insert(p[i].h);
		} else {
			if(Max == p[i].h && s.count(p[i].h) == 1){
				s.erase(Max);
				Max = *s.rbegin();
				v.push_back({p[i].x, p[i].h});
				v.push_back({p[i].x, Max});
			} else {
				s.erase(s.find(p[i].h));
			}
		}
	}
	
	printf("%d\n",(int)v.size());
	for(auto [x,y] : v){
		printf("%d %d\n",x, y);
	}
	

	return 0; 
}
```

    
    
```diff
 !  2022-05-08💐
```
<br>
<br>
<br>

[返回](#jump0)

<span id="jump3"></span>

#  [Operations on a Matrix](https://atcoder.jp/contests/abc253/tasks/abc253_f)
	
      不会写呀！！！
      首先对于这个二维的矩阵我们需要先搞清楚对他的操作。
      对于每一行，我们可以将其这一行全部修改为某一个数
      对于列，我们可以将其全部进行区间加。
      
      那么我们想一下，对于我们想要查询的一个点(i, j)我们需对其行与列分开进行判断。
      对于行的操作是覆盖性的，那么我们需要的就是离当前查询步骤最近的一次对本行修改的步骤。
      那么我们就知道了我们其是要统计的列的变化是从那次修改到现在对本列修改的步骤。
      我们只需要将对行修改的x加上对列的修改就是答案。
      
      那么我们可以对列进行线段树进行维护，对行进行记录一个时间戳，即最近的修改他的步骤。
      那么我们对列可以进行类似于主席树的前缀和的思想，假如上一次对其的修改的时间戳为t1,当前时间为t2，
      那么对列的修改我们需要记上的就是sum(t2) - sum(t1),所以我们可以将操作存下来，在每一个t1将其对应的
      t2减去当前的单点查询，在t2对答案加上当前的单点查询，就可以输出答案了。
      
 ```C++
 # include "bits/stdc++.h"

using namespace std;
using i64 = long long;
const int maxn = 2e5 + 10, mod = 998244353;

struct node{
    int opt, val, l, r;
};
int last[maxn];
vector<node >sub[maxn];
pair<int,int>rem[maxn];
i64 ans[maxn];

struct SegmentTree{
    i64 info[maxn << 2], lazy[maxn << 2];
    void pushdown(int p){
        if(lazy[p]){
            lazy[p << 1] += lazy[p];
            lazy[p << 1 | 1] += lazy[p];
            info[p << 1] += lazy[p];;
            info[p << 1 | 1] += lazy[p];
            lazy[p] = 0;
        }
    }
    void update(int p, int l, int r, int L, int R, int x){

        if(l >= L && r <= R){
            if(l == r) info[p] += x;
            lazy[p] += x;
            return;
        }
        pushdown(p);
        int mid = l + r >> 1;
        if(L <= mid) update(p << 1, l, mid, L, R, x);
        if(R > mid)  update(p << 1 | 1, mid + 1, r, L, R, x);
    }
    i64 query(int p, int l, int r, int x){
        if(l == r){
            return info[p];
        }
        pushdown(p);
        int mid = l + r >> 1;
        if(x <= mid) return query(p << 1, l, mid, x);
        else         return query(p << 1 | 1, mid + 1, r, x);
    }
}tree;
int main()
{

    int n, m, q;  scanf("%d %d %d",&n,&m,&q);
    for(int i = 1; i <= q; i++){
        int opt;  scanf("%d",&opt);
        if(opt == 1){
            int l, r, x;  scanf("%d %d %d", &l, &r, &x);
            sub[i].push_back({1, x, l, r});
        } else if (opt == 2){
            int row, x;  scanf("%d %d",&row, &x);
            rem[row] = {i, x};
        } else {
            int x, y;  scanf("%d %d",&x,&y);
            int id = rem[x].first, val = rem[x].second;
            sub[id].push_back({3, val, i, y});
            sub[i].push_back({2, val, i, y});
            ans[i] += val;
        }
    }

    for(int i = 1; i <= q ; i++){
        for(auto [opt, val, l, r] : sub[i]){
            if(opt == 1){
                tree.update(1, 1, m, l, r, val);
            } else if (opt == 3) {
                ans[l] -= tree.query(1, 1, m, r);
            }  else if (opt == 2) {
                ans[l] += tree.query(1, 1, m, r);
                printf("%lld\n",ans[l]);
            }
        }
    }
    return 0;
}
 ```

 ```diff
 !   2022-05-28😆
 ```
      
      
      
      
      
      
      
      
      
      
