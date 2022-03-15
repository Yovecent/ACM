#  🧢[CCPC Harbin 2021. (G. Damaged Bicycle)](http://oj.daimayuan.top/problem/380)

    真的好难呀！！
    学长可是靠着这道题拿的最后的银牌呀！！！
    真的感觉到了自己和拿牌的差距😢
    
>    状压dp + 期望

    首先我们来系统的思考一下这道题。
    
    首先我们一定是会赶紧找到一个车然后骑回去，或者说走回去。
    那么我们需要考虑的点就只有起始位置和所有的车的位置(即直奔车过去的)。
    
    我们到达一个车点会有两种情况。
    
    good:
    如果是好的，我们就直接骑回去了，直接起飞。
    
    bad：
    然后我们如果现在的这个车是坏车，那么我们有两种选择：
    (1)直接开摆， 然后慢悠悠的走回去。
    (2)我们赶紧去找下一辆车还没有去过的车
    
    
    对于bad的两个情况我们只需要选择其中一个就可以了，并不是1/2的概率。
    因为对于每一个车坏掉的概率是确定的，我们就可以求出从这个点回去的期望时间，
    同时走回去的时间我们也是知道的，
    那么我们就只需要折中的选择其中耗时最小的就可以了，然后加上骑回去的。
    
    这里我们定义 dp[S][u]表示： 此时处于u好点，并且已经遍历过S的回去的最小期望时间。
    那么我们的状压dp的遍历就是逆序的。
    
    对于终极状态就是我已经遍历过所有状态，并且处于这个点，那么对于bad状态我就只可以选择走回去。
    
    这个用dfs能够够好的解释这个转移过程。
    
    对于当时只是想到了期望，单纯的从起始找到离他最近的车，不断递归，到那时不一定就是每次离现在这个点
    最近就是最好策略，所以状压才是正确的。
    
ACcode
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;
const int maxn = 1e5 + 10, INF = 0x3f3f3f3f;
typedef pair<int,int> Pii;

int vis[20][maxn], dis[20][maxn];
double w, r, pi[20];
int n, m, bike[20], id[20], k;
vector<Pii>v[maxn];
struct info{
            
    int u, w;
    info(){};
    info(int u,int w):u(u), w(w){};
    friend bool operator < (info x,info y){
        return x.w > y.w;
    }
};
priority_queue<info>q;

void dijistra(int k){

    for(int i = 1; i <= n ; i++){
        dis[k][i] = INF;
        vis[k][i] = 0;
    }
    dis[k][bike[k]] = 0;
    q.push(info(bike[k],0));

    while(!q.empty()){

        info x = q.top(); q.pop();
        if(vis[k][x.u]) continue;
        vis[k][x.u] = true;

        for(auto to : v[x.u]){
            if(dis[k][to.first] > dis[k][x.u] + to.second){
                dis[k][to.first] = dis[k][x.u] + to.second;
                q.push(info(to.first,dis[k][to.first]));
            }
        }
    }
}

double dp[(1 << 20)][20];
double dfs(int state,int u){

    if(dp[state][u]) return dp[state][u];
    double good = (1 - pi[u]) * dis[u][n] / r;
    double bad = pi[u] * dis[u][n] / w;

    for (int mask = 0; mask < k; mask++) {

        if(state & (1 << mask)) continue;
        bad = min(bad, pi[u] * (dis[u][id[mask]] / w + dfs(state | (1 << mask), mask)));
    }
    dp[state][u] = bad + good;
    return dp[state][u];

}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    cin >> w >> r >> n >> m;
    for (int i = 0; i < m; i++) {

        int u,to,w;
        cin >> u >> to >> w;
        v[u].push_back({to,w});
        v[to].push_back({u,w});
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> bike[i] >> pi[i];
        pi[i] /= 100; 
        id[i] = bike[i];
    }

    for(int i = 0 ;i < k; i++) {
        dijistra(i);
    }
    bike[k] = 1; pi[k] = 1;
    dijistra(k);

    if (dis[k][n] == INF) {

        cout << "-1" << endl;
        return 0;
    } else {

        dfs(0, k);
        cout << fixed << setprecision(6) << dp[0][k] << endl;
    }


    return 0;
}
```

```diff
!   🐈‍2022-03-16
```
    
