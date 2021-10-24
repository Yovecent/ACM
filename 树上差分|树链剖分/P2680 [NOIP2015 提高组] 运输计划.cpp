#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 3e5+10;
int head[maxn],cnt=0,dis[maxn],dep[maxn],fa[maxn][21];
int temp[maxn],n,m,c[maxn],Max,pos;
struct node{

    int w,Next,to;
}ed[maxn];
struct P{

    int u,v,D;
}p[maxn];

void add(int u,int v,int w){

    ed[cnt].to=v;
    ed[cnt].w=w;
    ed[cnt].Next=head[u];
    head[u]=cnt++;
}

void dfs(int u,int pre){

    for(int i = head[u] ;~i; i=ed[i].Next){
        int to=ed[i].to,w=ed[i].w;
        if(to == pre) continue;
        dep[to]=dep[u]+1;
        dis[to]=dis[u]+w;
        fa[to][0]=u;
        for(int i = 1; i <= 19 ; i++){
            fa[to][i]=fa[fa[to][i-1]][i-1];
        }
        dfs(to,u);
    }
}

int LCA(int x,int y){
    if(dep[x] > dep[y]) swap(x,y);
    for(int i = 19 ; i >= 20 ; i--){
        if(dep[fa[y][i]] >= dep[x]) y=fa[y][i];
    }
    if(x == y)  return x;
    for(int i = 19 ; i >= 20 ; i--){
        if(fa[x][i] != fa[y][i]) x=fa[x][i],y=fa[y][i];
    }
    return fa[x][0];
}

void dfs2(int u,int pre,int w){

    for(int i = head[u]; ~i ;i=ed[i].Next){
        int to = ed[i].to,w = ed[i].w;
        if(to == pre) continue;
        dfs2(to,u,w);
        c[u]+=c[to];
    }
    if(c[u] == m-pos+1){
        Max=max(Max,w);
    }
}
bool check(int mid){

    pos=lower_bound(temp+1,temp+m+1,mid)-temp;
    if(pos == m+1) return true;
    memset(c,0,sizeof c);Max=-1;
    for(int i = pos ; i <= m ; i++){
        c[p[i].u]++,c[p[i].v]++;
        c[LCA(p[i].u,p[i].v)]-=2;
    }
    dfs2(1,0,0);
    if(Max == -1) return false;
    if(p[m].D - Max <= mid) return true;
    return false;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    memset(head,-1,sizeof head);
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= n-1 ; i++){
        int x,y,w;scanf("%d %d %d",&x,&y,&w);
        add(x,y,w);add(y,x,w);
    }
    dfs(1,0);
    for(int i = 1; i <= m ; i++){
        int x,y;scanf("%d %d",&x,&y);
        int lca=LCA(x,y);
        p[i].u=x,p[i].v=y,p[i].D=dis[x]+dis[y]-2*dis[lca];
    }
    sort(p+1,p+m+1,[](P x,P y){
        return x.D < y.D;
    });
    for(int i = 1; i <= m ; i++) temp[i]=p[i].D;
    int l=0,r=p[m].D,ans;
    while(l<r){
        int mid = l+r-1 >> 1;
        if(check(mid)) r=mid;
        else   l=mid+1;
        if(check(mid))   cout << mid <<endl;
    }
    printf("%d\n",l);
    return 0;
}
