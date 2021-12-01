# [	Edge Groups](https://ac.nowcoder.com/acm/contest/24872/G)

    😧写这道题柑橘脑子瓦特了,比赛的时候可一定要高度集中。
   
    首先承认树是一个好东西，很多时候我发现如果我们只是把他当做一个图去做的话，总是会很困难但是如果我们可以把转化成树，或是按照dfs的思想去看图的话，可以使得问题更加轻易地解决。
   
    在这道题里，如果把它看成一个图，可能会毫无头绪，因为在图里面没有一个固定的遍历方法怎么能求出来呢？
   
    但我们把它看作是一个树的话，就很好做了，因为他到父节点的的边只有一条，那么我们就可以去数它的子节点可以用的边有几条，如果子节点的边数为偶数，那么就一定是把所有的偶数节点都连到当前
    节点，上面的那条节点连到上面，不然的话就会出现奇数条边。如果有奇数条边，那么上面那条边就要连到当前这个节点，这样才能保证是偶数条边。
   
    所以我们就直接dfs就可以了。
   
    其次这里用到了一个排列组合当统计方法！！！！
   
    把n个物品两两组队有几种方法。这里保证n是偶数。
   
    可以用dp的思想。dp[i]表示有i个物品的时候的方案数，那么我们在加一个物品之后，我们只考虑第一个物品。第一个物品共有n-1中组队的方法，而我们一旦确定第一个物品，此时就生下了n-2个物品，
    又转化成了之前求过的子问题。
```C++
    dp[0]=1;
    for(int i = 2 ; i <= n ; i++){
          dp[i]=dp[i-2]*(i-1)%mod;
    }
```

    这里其实不用预处理，因为cnt大大小一共是n，所以时间复杂度是O(n)
AC代码：
```C++
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdio>
#include <algorithm>

#define int long long
using namespace std;
const int mod = 998244353;
const int maxn = 1e5+10;

vector<int>v[maxn];
int dp[maxn],n,ans=1;
int dfs(int u,int pre){

    int cnt=0;
    for(auto x : v[u]){
        if(x == pre) continue;
        if(!dfs(x,u))  cnt++;
    }
    for(int i = 1; i <= cnt ; i+=2) ans=ans*i%mod;
    return (cnt&1);
}
signed main()
{   
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    scanf("%lld",&n);
    for(int i = 1; i < n ; i++){
        int u,to;scanf("%lld %lld",&u,&to);
        v[to].push_back(u);v[u].push_back(to);
    }
    dfs(1,0);
    printf("%lld\n",ans);
    return 0;
}
```
