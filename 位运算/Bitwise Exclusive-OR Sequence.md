# 	[Bitwise Exclusive-OR Sequence](https://ac.nowcoder.com/acm/contest/24346/B)

    🧸这次沈阳站是第一次参加的比赛，最终还是打铁了，继续努力吧！！
    
    首先对于所有有关系的元素，我们都可以将其归并为一个连通块，就类似于并查集的思想，这里其实直接建树就可以了，在跑的的时候，就相当于在树上跑，联通在一起的一次都跑完。
    
    因为这些数都是小于1e9的，也就是说我们只用考虑30位就可以了。而我们对于每一位考虑，当我们设出这个数的这一位是1的时候，我们就可以直接去跑整个连通块，看一下一共有几个1，
    几个0，也就是说，在符合条件的情况下一个连通块的所有元素在某一位会被分成0 1 的两种情况，计算出来最小的就可以了那么我们肯定是吧多的设为0，少的设为1。
    
    不成立的情况就是说，我们已经设过某一位了，在又遍历到她的时候与该有的值不一致，就说明条件不对。
    
```C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
const int maxn =1e5+10;

vector<PII>v[maxn];
int val[maxn][35],n,m;
bool vis[maxn][35],ok;
int tot,sum;
ll ans=0;

void dfs(int u,int pre,int k,int x){

    sum++;
    tot+=x==1;
    vis[u][k]=true;
    val[u][k]=x;
    for(auto to : v[u]){
        if(to.fi == pre) continue;
        int xt=x;
        if((to.se >> k )&1) xt^=1;
        if(vis[to.fi][k]){
            if(val[to.fi][k] != xt){
                ok=false;return;
            }
        }
        else{
            dfs(to.fi,u,k,xt);
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    scanf("%d %d",&n,&m);
    for(int i = 1 ; i <=  m ;i++){
        int u,to,w;scanf("%d %d %d",&u,&to,&w);
        v[u].push_back({to,w});v[to].push_back({u,w});
    }
    for(int i = 1; i <= n ; i++){
        for(int j = 0; j < 30 ; j++){
            if(vis[i][j])continue;
            tot=sum=0;
            ok=true;
            dfs(i,0,j,0);
            int mi=min(tot,sum-tot);
            if(!ok){
                printf("-1\n");return 0;
            }
            // cout << mi << "-----"  << sum << " "<< tot << endl;
            ans+=1ll*(1<<j)*mi;
        }
    }printf("%lld\n",ans);
    return 0;
}

```
