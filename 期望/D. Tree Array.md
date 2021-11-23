# [D. Tree Array](https://codeforces.com/contest/1541/problem/D)

    🥪期望+dp+LCA(考察的东西太多了，不愧是道2300分的题目)
    
    
    首先我们先来理一下思路，我们整道题要求的其实就是一个逆序对的期望，只不过他想让我们化成分子分母的形式，
    然后在用逆元求出答案。这样的话很困难，因为如果我们想要直接求出来的话，就必须通分，通分的过程太难了，
    ♦️小菜鸡想了好久都不知道该咋弄。
    
    
    所以我们需要转换思想，我们无非就是求出每一种可能的排序下的可能期望。
    首先我们需要做的肯定是以每一个点都作为根，然后去找到所有的通路，然后再算出每一对逆序对对答案的贡献。
    我们并不需要将路走完(即将一整个序列先找出来)，我们只需要考虑每一对逆序对就可以了。
    因为最后对答案贡献的是逆序对的数量。所以我们求得其实就是每一个逆序对期望，期望相加就是总的期望。
    
    然后我们来考虑一下怎么求逆序对的期望。
    首先我们考虑点x,y(x>y)，所以我们如果能够使序列中xy逆序对对答案有贡献，那就是说x应该比y先取。
    因为我们是在树中沿路径不断延伸的，所以会导致我们有多排列顺序而使得x在y的前面，而真正对xy的取法有限制的
    就只有x到y的最短路径上的点。因为我们取其他的只是在x,y使xy得在序列中的位置发生了改变，而相对顺序并没有
    发生变化，所以我们可以求出xy的公共祖先，如果我们想要让x先被选到，那么就说明我们应该把lca到x，的点都选到，
    而lca到y的父节点的点被选到也是可以的，因为我们只需要保证这段路中y是最后被选到的即可。
    
    这样就把问题转化成了另一种，即左箱子里有len1个球，右箱子里有len2个球，我们需要求出先把做箱子里面的球取完
    的概率是多少。
    
    这里用了一个dp
    
    dp[i][j]左边有i个东西，右边有j个东西，先取完左边的概率。
    首先初始化左边空的概率是1，右边空的概率是0，然后dp，因为我们第一下不是拿左边，就是拿右边，就又转化成了之前
    的两种状态，除以2就是当前的概率。
```C++
for(int i = 1; i <= n ; i++){
        dp[i][0]=0;
        dp[0][i]=1;
    }int inv=ksm(2,mod-2);
    for(int i = 1; i <= n ; i++){
        for(int j = 1; j <= n ; j++){
            dp[i][j]=(dp[i-1][j]+dp[i][j-1])*inv%mod;
        }
    }
```
    最后还需要除以n，因为我们有n种建树的情况。
    
AC代码如下：
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define int long long 
using namespace std;
typedef long long ll;
const int maxn =2e5+10;
const int mod = 1e9+7;

vector<int>v[250];
int dp[250][250],n;
int fa[250][10],dep[250];
int ksm(int a,int b){
    
    int res=1;a=a%mod;
    while(b){
        if(b&1) res = res*a%mod;
        a=a*a%mod;
        b>>=1;
    }return res;
}
int dfs(int u,int pre){

    dep[u]=dep[pre]+1;
    fa[u][0]=pre;
    for(int i = 1; i <= 8 ; i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(auto x: v[u]){
        if(x==pre) continue;
        dfs(x,u);
    }
}
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i = 8 ; i >= 0 ; i--){
        if(dep[fa[x][i]] >= dep[y]) x=fa[x][i];
    }
    if(x == y) return x;
    for(int i = 8 ; i >= 0 ; i--){
        if(fa[x][i] !=fa[y][i]){
            x=fa[x][i],y=fa[y][i];
        }
    }
    return fa[x][0];
}
void solve(){

    for(int i = 1; i <= n ; i++){
        dp[i][0]=0;
        dp[0][i]=1;
    }int inv=ksm(2,mod-2);
    for(int i = 1; i <= n ; i++){
        for(int j = 1; j <= n ; j++){
            dp[i][j]=(dp[i-1][j]+dp[i][j-1])*inv%mod;
        }
    }
    int ans=0;
    for(int i = 1 ; i <= n ; i++){
        dfs(i,0);
        for(int x = 1 ; x <= n ; x++){
            for(int y=1; y < x ;y++){
                int lc=lca(x,y);
                int dx=(dep[x]-dep[lc]);
                int dy=(dep[y]-dep[lc]);
                ans=(ans+dp[dx][dy])%mod;
            }
        }
    }
    ans=ans*ksm(n,mod-2)%mod;
    printf("%lld\n",ans);
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
        v[u].push_back(to);v[to].push_back(u);
    }
    solve();
    return 0;
}
```
    
  
