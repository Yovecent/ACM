# 🏹最短路之终极奥义

  ## (1)💿Dijkstra
  
    首先我们来谈一下Dijkstra的算法核心:
    利用贪心的思想，找出当前最小的并且没有作过扩散点的点，去松弛周围的点(dis[to] < dis[u] + w)，通过n个点的松弛，从而找到每一个点到
    起点的单源最短路。这样朴素的Dijkstra的时间复杂度为O(n^2)。
    
    但我们在进行n次松弛时，首先要找到那个最小的符合的点，所以对于优化我们考虑使用优先队列。
    
    🩹首先这个算法一定是正确的，我们来考虑一下，我们找出的当前最短的一个点，并且他是没有被标记的，那么就一定是他的最短路，为什么呢？
    
    因为既然这个点能被我们找出来，那说明此时从起点到所有点中，这条路是最短的，如果我们想要通过其他点在跑到这个点，那就需要用他的dis在
    加上那个点到当前点的路径长来更新，但是这个dis已经比他长了，那么就永远不会更新。
    
    使用了堆优化之后时间复杂度为O(mlog(m))
    
```C++
struct node{
    int u,w;
    friend bool operator<(node x,node y){
        return x.w>y.w;
    }
};
void  Dijkstra(){
    
    priority_queue<node>q;
    memset(dis,INF,sizeof dis);
    memset(vis,0,sizeof vis);
    dis[1]=0;
    q.push({0,1});
    while(q.size()){
        node p=q.top();q.pop();
        if(vis[p.u]) continue;
        vis[p.to]=true;
        for(auto to : v[p.u]){
            if(dis[to.fi] > dis[p.u]+to.se && !vis[to.fi]){
                dis[to.fi] = dis[p.u]+to.se ;
                q.push({dis[to.fi],to.fi});
            }
        }
    }

}
```
 ##  🌂Bellman-Ford  
    
    这个算法的思想与Dijkstra类似但有不同。
    我们想一下，对于一个有n个点的图，如果我们想要求出从起点到每一个点的最短路是不是最多只用更新n-1次就够了！！
    因为我们每一次松弛都会找到至少一个点的最短路，但是我们并不知道是那个点。(因为从起点到每一个点的最短路都不超过n-1条，
    每次我们都为这条更新了一段，那么最多只用n-1下)
    于是每一次我们只要通过我们已知的一条有向边来更新一下两个端点的最短路
    
```C++
for(int i = 1; i <= n ; i++){
   for(int i = 1;i <= m ; i++){
      if(dis[v[i]] > dis[u[i]] + w ){
          dis[v[i]=dis[u[i]]+w
      }
   }
}
```
    这样的话时间复杂度就是n*m。所以效果并不是很好。
    我们想对于每一次松弛我们并不是都是成功的，有的点可以被松弛，但有的点不会。所以我们想优化的地方就在这里。
    对于一个点，如果这次没有被松弛，那么他也不会参与下次的松弛了，(这里是指一轮下来，即他被更新过之后看是否还能被更新)，
    因为只有他被松弛了，才会对接下来的点进行松弛，如果他没有被松弛，那么他对周围的点的作用效果不是还是一样的嘛！！)
    所以我们只需要把能够成功松弛的点装进队列里面。
    
```C++
void  Bellman-Ford(){
    
    queue<int>q;
    memset(dis,INF,sizeof dis);
    memset(vis,0,sizeof vis);
    dis[1]=0;
    q.push(1);vis[1]=true;
    while(q.size()){
        int p=q.front();q.pop();
        vis[p]=false;
        for(auto to : v[p]){
            if(dis[to.fi] > dis[p]+to.se && !vis[to.fi]){
                dis[to.fi] = dis[p]+to.se ;
                if(!vis[to.fi]){
                    q.push(to.fi);
                    vis[to.fi]=true;
                }
            }
        }
    }

}
```
    🍬但往往Blleman的时间复杂度要比Dijkstra要高，那Blleeman的好处在哪里呢？
    
    因为Blleeman可以用于存在负边的图，而Dijkstra不可以。为什么呢？？？
    
    我们想一下Dijksra的思想是什么？贪心。贪心的话总是会取最小的边，于是对于现在所取到的一个点u，我们会是为此时的dis就是u的最短路，
    于是便会把vis[u]变为true,但是如果存在负边的话，那么我们可能会使得本来很大的dis变得很小，从而从新找到一条去往u的最短路，但这时
    我们已经把u置为true了，也就不会更新了，所以Dijkstra只能用来判断正权边。
    
    而Blleman每次都会把成功更新的点加入松弛点然后去更新其他点，所以只要不出现负环就可以成功的找出每一个点的最短路。
    
    而负环的意思是使得最短路变为负数了，那么我们就更新的次数不是n-1次了，而是超过n-1次而无限的更新。所以我们在进行Bellman时，
    如果在更新了n-1次后还能更新说明存在负环。
```C++
int cnt[maxn];//次数超过了n-1次说明有负环
bool  Bellman-Ford(){
    
    queue<int>q;
    memset(dis,INF,sizeof dis);
    memset(vis,0,sizeof vis);
    dis[1]=0;
    q.push(1);vis[1]=true;cnt[1]=1;
    while(q.size()){
        int p=q.front();q.pop();
        vis[p]=false;
        for(auto to : v[p]){
            if(dis[to.fi] > dis[p]+to.se && !vis[to.fi]){
                dis[to.fi] = dis[p]+to.se;
                cnt[to.fi]++;
                if(cnt[to.fi] >= n) return false;
                if(!vis[to.fi]){
                    q.push(to.fi);
                    vis[to.fi]=true;
                }
            }
        }
    }return true;

}
```
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
