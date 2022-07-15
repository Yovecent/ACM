## 🏁SPFA算法

    🥂SPFA算法是在Bellman-Ford算法之上升级而来的。
    因为我们对于整幅图，我们只需要更新n-1次就够了，因为对于每两个点之间的最短路经过的点一定不会超过n个，而我们是从起始点开始的，那也就说明了
    我们最多还会再增添n-1个点，也就是更新n-1次。
    但是每一次我们都会把所有的m条边都更新一下最短路，但实际上这并不划算，因为有的点并没有更新。
    而我们把它转化成队列的形式如果只是单纯的添加其实是和Bellman-Ford是一样的，而SPFA的优化之处在于他每次只把成功优化的点加进去。
    因为如果一个点都没有被松弛，那么他也不会去松弛其他的点。
    
    而对于队列来说，其是一定正确的。因为我们每次都把成功更新的点加入到队列之中，然后去更新其他的点，这样总会达到一个尽头而使得无法更新。
    
    但对于SPFA来说更重要的时来判断负环。
    
    有bfs版的，其实就是队列。
    
    对于cnt来说，其是记录了一条最短路中共有几个点，当点数超过了n个时就代表形成了负环。
    
```C++
bool SPFA(int u,double mid){

    q.push(1);
    dis[1]=0;
    while(q.size()){
        int u=q.front();q.pop();
        vis[u]=false;
        for(int i=head[u] ; ~i ;i=ed[i].Next){
            int to=ed[i].to;double w=ed[i].w;
            if(dis[to] > dis[u] + w){
                cnt[to]=cnt[u]+1;
                if(cnt[to]>=n) return false;
                dis[to]=dis[u]+w;
                if(vis[to]){
                    q.push(to);
                }
            }
        }
    }
}
```

    而对于判负环来说，dfs版会更有效率，其实bfs与dfs最终达到的效果都是一样的，最终都无法更新而停止更新。
    只是bfs进行了进栈就再次松弛，而bfs是按照顺序去松弛，dfs更能及时的发现负环，但是如果没有负环的情况下却要比bfs慢。
```C++
int tot;
bool SPFA () {
	
	stack<int> q;
	for (int i = 1; i <= n; i++) {
		q.push(i);
		vis[i] = true;
		cnt[i] = 0;
	}
	
	while (!q.empty()) {
		int u = q.top();
		q.pop();
		vis[u] = false;
		
		for (auto [v, w] : adj[u]) {
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;
				if (++tot >= 1e5) return true; 
				if (cnt[v] >= n) return true;
				if (!vis[v]) {
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	return false;
}
```

这里附上一道判负环的题目
[P3199 [HNOI2009]最小圈](https://www.luogu.com.cn/problem/P3199)

```C++
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
typedef pair<int,double>PII;
const int maxn = 1e4+10;
const int maxm = 3e3+10;

struct node{
    int to,Next;
    double w;
}ed[maxn<<1];
int n,m,cnt=0,head[maxn<<1];
double l=1e18,r=0;
double dis[maxn];
bool vis[maxn];

void add(int u,int v,double w){
    ed[cnt].to=v;
    ed[cnt].w=w;
    ed[cnt].Next=head[u];
    head[u]=cnt++;
}
bool SPFA(int u,double mid){

    vis[u]=true;
    for(int i=head[u] ; ~i ;i=ed[i].Next){
        int to=ed[i].to;double w=ed[i].w;
        if(dis[to] > dis[u] + w-mid){
            dis[to]=dis[u]+w-mid;
            if(vis[to] || SPFA(to,mid)) return true;

        }
    }vis[u]=false;
    return false;
}
bool check(double mid){

    for(int i = 1; i <= n ; i++){
        dis[i]=vis[i]=0;
    }
    for(int i = 1; i <= n ; i++)  if(SPFA(i,mid)) return true;
    return false;
}
int main()
{   
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    memset(head,-1,sizeof head);
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= m ; i++){
        int u,to;double w;scanf("%d %d %lf",&u,&to,&w);
        add(u,to,w);
        l=min(l,w);r=max(r,w);
    }
    while(r-l>1e-9){
        double mid=(l+r)/2;
        if(check(mid)){
            r=mid;
        }
        else l=mid;
    }printf("%.8lf\n",r);
    return 0;
}
```
