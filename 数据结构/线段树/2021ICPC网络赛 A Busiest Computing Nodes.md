# 💥线段树真是个好东西  
🐪这道题考查的是线段树和二分的结合  

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
