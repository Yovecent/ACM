⚖️[E. Not Escaping](https://codeforces.com/contest/1627/problem/E)
====
    说实话这道题其实很显然的就可以看出来是dp，但是我觉得这道题的难点就在于对于第二层的划分。
    
    首先我们考虑，对于dp[i][j]表示到达第i层第j个房间的付出值，那么其实j我们并不用对于每个都更新，因为我们想要往上走的我们
    只能沿着梯子往上走，所以我们对于每层的j我们就只用记录有梯子的地方，然而每一层对另一层的更新类似于女生赛的，因为他只能往上走，
    所以我们需要做的就是确定每一层有多少情况，然后再用这一层的情况去更新上面一层。
    
    这里很巧妙地利用了map,tuple,vector
    
    首先因为我们并不知道每一层有多少状态，所以我们可把dp数组换成 map<int,ll>dp[maxn]
    然后我们还需要存梯子，又因为在(i,j)可能会有多个梯子，通向不同的地方，所以map的值我们需要改一下map<int,TIIL>go[maxn]
    这里第一次见到了tuple，他就类似于pair，只不过他存三个
    
    typedef tuple<int,int,long long>TIIL
    
    然后就是对于每一层内的更新，因为x[i]是一个定值，所以我们只需要按需给相邻的点更新即可，
    因为我们不知道哪一点使现在最划算的点，那么我们就正向更新一边，反向更新一边，那么这个点就可以给所有的点都更新到最优的情况了
    
AC代码：
===
```C++
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <map>

#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef tuple<int,int,ll>TIIL;
const int maxn = 1e5+10;
const ll e60 = 1ll<<60;

int n,m,k;
int x[maxn];
map<int,ll>dp[maxn];
map<int,vector<TIIL>>go[maxn];

void update(int i,int j,ll val){

	dp[i][j]=min(dp[i][j],val);
}
void solve(){

	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1; i <= n ; i++){
		scanf("%d",&x[i]);dp[i].clear();
		go[i].clear();
	}
	for(int i = 1; i <= k ; i++){
		int a,b,c,d,h;scanf("%d %d %d %d %d",&a,&b,&c,&d,&h);
		go[a][b].push_back({c,d,h});
		dp[a][b]=dp[c][d]=e60;
	}
	dp[1][1]=0,dp[n][m]=e60;
	for(int i = 1; i <= n ; i++){
		if(!dp[i].size()) continue;
		for(auto u = dp[i].begin(),v=u;++v!=dp[i].end();++u){
			if(u->se != e60) update(i,v->fi,u->se+1ll*(v->fi-u->fi)*x[i]);
		}
		for(auto u = dp[i].rbegin(),v=u;++v!=dp[i].rend();++u){
			if(u->se != e60) update(i,v->fi,u->se+1ll*(u->fi-v->fi)*x[i]);
		}
		for(auto [u,val] : dp[i]){
			for(auto [c,d,h] : go[i][u]){
				if(val != e60) update(c,d,val-h);
			}
		}
	}
	if(dp[n][m] == e60) printf("NO ESCAPE\n");
	else                printf("%lld\n",dp[n][m]);
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
	int t;scanf("%d",&t);
	while(t--){
	  solve();
	} 
	return 0;
}
```
```diff
!    ✳️2021-01-16
```
