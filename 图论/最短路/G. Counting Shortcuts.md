#   🥖[G. Counting Shortcuts](https://codeforces.com/problemset/problem/1650/G)

    在没有学习最短路之前，其实一直以为bfs就是最短路，后来才知道最短路与其不同的地方在于他的边权不一定为1。
    而在这道题里面，因为边权可以视为1，所以就退化成了bfs。
    
    这道题其实求得就是最短路与次短路。
    我们可以使用bfs
    定义 dp[i][0]为从起点到这个点的最短路的个数，dp[i][1]为从起点到这个点的次短路(多走一步)的个数。
    
    其实就是按照bfs的方法
    (1)  !vis[i] 那就把u的信息全部付给x
    (2)  dis[x] == dis[u] + 1 那就是说，这也是到达x的最短路，那就把u的信息加付到x上。
    (3)  dis[x] == dis[u] 那我们就可以求出x的次短路,把dp[u][0]加到 dp[x][1]上。
    
    但是这样是错的，因为我们只能保证dp[u][0]时正确的，而dp[u][1]不一定。
    
    因为dp[u][0]是由上一步更新出来的，如果到达这一步，那上一步一定都更新完了，那就说明dp[u][0]求完了。
    但是dp[u][1]是由同一层的点更新的到这个点的，所以我们遍历到这点时，其他这一层的点可能还没有更新到他，
    所以我们只需走两个dfs，即让dp[u][1]的更新滞后一下。更新完这一层后再让这一层去更新下一层的dp[x][1]。

AC代码：
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;
const int INF = 0x3f3f3f3f, mod = 1e9+7;

vector<int>v[200010];
int dp[200010][2],dis[200010];
bool vis[200010],us[200010];//vis第一层bfs标记，us第二层bfs标记
queue<int>q;

void bfs(int s,int e,int n){

    q.push(s);
    for(int i = 1; i <= n ; i++){
        vis[i] = us[i] = 0;
        dp[i][0] = dp[i][1] = 0;
    }
    dis[s] = 0; dp[s][0] = 1; 
    vis[s] = true;
    while(!q.empty()){

        int u = q.front();  q.pop();

        bool ok = false;
        for(auto x : v[u]){

            if(!vis[x]){
                dis[x] = dis[u] + 1;
                vis[x] = true;
                q.push(x);
                dp[x][0] = dp[u][0];
            } else if (dis[x] == dis[u] + 1) {
                if(!us[u]) dp[x][0] = (dp[u][0] + dp[x][0]) % mod;
                if(us[u]) dp[x][1] = (dp[x][1] + dp[u][1]) % mod;
            } else if (dis[x] == dis[u] && !us[u]){
                int a = dp[x][0], b = dp[u][0];
                dp[x][1] = (dp[x][1] + b) % mod;
            }
        } 
        if(!us[u]){
            q.push(u);
            us[u] = true;
        }
    }
    cout << (dp[e][0] + dp[e][1]) % mod << endl;
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;  cin >> t;
    while(t--){

        int n,m;  cin >> n >> m;
        int s,e;  cin >> s >> e;
        for(int i = 1; i <= n ; i++) v[i].clear();
        for(int i = 1; i <= m ; i++){
            int u,to;
            cin >> u >> to;
            v[u].push_back(to);
            v[to].push_back(u);
        }
        bfs(s,e,n);
    }
    return 0;
}
```


+    (2)看了一位大佬的写法

    
    分别求起点和终点的bfs，然后枚举每一个可能产生次短路的端点。
    首先dis1[i] + dis2[i] == dis2[t]表示这个点经过了最短路，那么我们可以把他的路程加一，
    即向他的其他边延申一下，同时如果 dis2[i] == dis2[x]的话，那也就只多了一条边，让
    答案加上dp1[i] * dp2[x]
    
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int mod = 1e9 + 7;

vector<int>v[200010],dis1(200010),dis2(200010);
vector<int>dp1(200010),dp2(200010);
queue<int>q;

void bfs(int s,int n){

    for(int i = 1; i <= n ; i++){
        dis1[i] = -1;
        dp1[i] = 0;
    }
    dp1[s] = 1, dis1[s] = 0;
    q.push(s);
    while(q.size()){

        int u = q.front();  q.pop();

        for(auto x : v[u]){
            if(dis1[x] == -1){
                dis1[x] = dis1[u] + 1;
                q.push(x);
            }
            if(dis1[x] == dis1[u] + 1){
                dp1[x] = (dp1[x] + dp1[u]) % mod;
            }
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;  cin >> t;
    while(t--){
        int n,m,s,t;  cin >> n >> m >> s >> t;
        for(int i = 1; i <= n ; i++) v[i].clear();

        for(int i = 1; i <= m ; i++){
            int u,to;   cin >> u >> to;

            v[u].push_back(to);
            v[to].push_back(u);
        }
        bfs(s, n);
        for(int i = 1; i <= n ; i++)  dis2[i] = dis1[i], dp2[i] = dp1[i];
        bfs(t,n);

        i64 ans = dp2[t];
        for(int i = 1; i <= n ; i++){
            if(dis1[i] + dis2[i] == dis2[t]){
                for(auto x : v[i]){
                    if(dis2[x] == dis2[i]){
                    
                        ans = (ans + 1ll * dp1[i] * dp2[x]) % mod; 
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
