# 最小生成树之 Prime算法

    🩹其实很久之前就知道这个算法，但当时觉得Kruskal挺容易理解的，然后就没有管过这个算法，只觉得晦涩难懂，但现在看来，
    其实认真看下去，其实也不是很难。
    
    
    🌂首先对于Kruskal和Prime的区别在于Kruskal是在不断的找边，所以适合稀疏图，
    然后Prime是在不断地找点，适合稠密图(因为Prime算法的时间复杂度是一定的O(n*n))。
    
    我们任意的选取一个起始点，然后利用dist数组去表示当前这个点与已经被选过的所有点中连边最短的一条，我们不断去找到
    与当前所在连通块不在一起的点的最短的边，然后不断地扩大，最终构成一个最小生成树。
    
    其次对于Prime算法，验证所给数据是否能构成最小生成树的方法是，当我们用minn去找出最小边时，如果没有被更新，
    那么就说明无法联通，因而可以验证。

[畅通工程](https://vjudge.net/contest/449748#problem/A)
```C++
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn =1e2+10;
const int INF =0x3f3f3f3f;
int G[maxn][maxn];
int dist[maxn],n,m;
bool vis[maxn];
void init(){
    for(int i = 1; i <= n ; i++){//初始化，将每一条边都设为无穷
        for(int j = 1; j <= n ; j++){
            if(i != j)G[i][j]=INF;
            else      G[i][j]=0;
        }
        dist[i]=INF;vis[i]=false;
    }
}
int Prime(){

    int S=1,sum=0;vis[S]=true;
    for(int i = 1; i <= n ; i++){
        dist[i]=G[i][S];
    }
    for(int i = 1 ; i < n ; i++){
        int minn=INF,op;
        for(int j = 1; j <= n ; j++){//每一次去更新一下未在连通块的点和在连通块的点的最短距离
            if(!vis[j] && dist[j] < minn){
                op=j;minn=dist[j];
            }
        }
        if(minn == INF) return -1;//验证是否能够成最小生成树
        sum+=minn;vis[op]=true;
        for(int j = 1; j <= n ; j++){
            if(!vis[j] && dist[j] > G[op][j]){
                dist[j]=G[op][j];
            }
        }
    }
    return sum;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    while(scanf("%d %d",&m,&n)&&m){
        init();
        for(int i = 1; i <= m ; i++){
            int u,v,w;scanf("%d %d %d",&u,&v,&w);
            G[u][v]=G[v][u]=w;
        }
        int t=Prime();
        if(m < n-1 || t == -1)  printf("?\n");
        else{
            printf("%d\n",t);
        }
    }
    return 0;
}
```
