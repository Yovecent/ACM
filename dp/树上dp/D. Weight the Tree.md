##  🤸[D. Weight the Tree](https://codeforces.com/contest/1646/problem/D)

    写这道题时真是瓦特了，一个典型的树形dp，一点都没有看出来。
    
    较容易推出来的是一个点是好点的话，周围的点就不是好点，因为他总会比他们大，也正是因为这个光往奇偶去判了。
    
    dp[u][1]:此点为好点，dp[u][0]:此点不为好点。
    那么状态转移方程为：
```diff
     dp[u][1] += dp[v][0]
!    dp[u][0] += max(dp[v][1],dp[v][0])
```
    同时这道题也不是单一的判断，有两个考虑因素，优先的是数量，其次是总量。
    那么用一个结构体，并定义了比较函数 < ,以及 += 使得其判断更方便。
    
    
```C++
#include <bits/stdc++.h>  

using namespace std;
using i64 = long long;
const int maxn = 2e5 + 10;

struct node{

    int x,y;
    node(){}
    node(int x,int y):x(x),y(y){};
    void operator += (const node &t){
        x += t.x,y += t.y;
    }
    friend bool operator < (node x,node y){
        if(x.x == y.x) return x.y > y.y;
        return x.x < y.x;
    }
};
vector<int>v[maxn];
node dp[maxn][2];
int is[maxn];

void dfs2(int u,int pre){

    for(auto x : v[u]){

        if(x == pre) continue;
        if(!is[u] ) is[x] = (dp[x][1] < dp[x][0]) ? 0 : 1;
        dfs2(x,u);
    }
}
void dfs(int u,int pre){

    dp[u][0] = node(0,1),dp[u][1] = node(1,v[u].size());
    for(auto x : v[u]){

        if(x == pre) continue;
        dfs(x,u);
        dp[u][0] += max(dp[x][1],dp[x][0]);
        dp[u][1] += dp[x][0];
    }
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 1; i < n ; i++){

        int u,to;
        cin >> u >> to;
        v[u].push_back(to);
        v[to].push_back(u);
    }
    if(n == 2){
        
        cout << 2 << " " << 2 << endl;
        cout << 1 << " " << 1 << endl;
        return 0;
    }
    dfs(1,0);
    is[1] = dp[1][0] < dp[1][1];
    dfs2(1,0);    
    i64 ans = 0;
    for(int i = 1; i <= n ; i++){
        if(is[i]) ans += 1ll * v[i].size();
        else      ans += 1;
    }
    cout << dp[1][is[1]].x << " " << ans << endl;
    for(int i = 1; i <= n ; i++){
        if(is[i]) cout << v[i].size() << " ";
        else      cout << 1 << " ";
    }
    cout << endl;
    return 0;
}
```
