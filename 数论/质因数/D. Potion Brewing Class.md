#  [D. Potion Brewing Class](https://codeforces.com/contest/1654/problem/D)

    首先我们根据n - 1可以简单的判断出来我们可以把他们放到一个树上，从一号节点去跑向所有的点。
    
    那么我们可以假设一号节点为1，那么我们可以求出每个节点的与一号节点的关系。
    即xi = a/b * x1
    那么我们求出所有的点与x1的大小关系之后，其实我们要做的就是求出所有分母的最小公倍数。然后让分数形式的数
    相加之后，乘上这个最小公倍数就可以了。
    但是这个最小公倍数我们其实不是很好求，因为如果考虑在求和过程中去约分的话很简单的可以知道会错的。
    (约分之后过了样例的弱鸡)
    
    那么我们就可以考虑把每一个数都转换成他的质因数集，即为分解质因数。
    那么我们在求取每一个数的分数形式时，就可以一并把最小公倍数求出来了。
    
    因为我们遇到一个分数，本来是要乘上的，但是我们只去统计每一个质因子的个数。
    如果在分母上就让这个质因数减去，如果在分子上就让他增加，然后对于每一个分数我们都求出来
    分母此时，质因数最多的个数，那么其就是到这一步时的最小公倍数的每一个质因数的个数。
    
    那么我们也就总结出了一种类型的题的解法。
    即为求出让多个分数乘上一个数使其化为整数并且没有公共质因数的形式的最小的数。
    从一个a[1] - a[n]，分子使其减，分母使其加，求出每一个质因数的最大个数。
    
    题解里面还有一个很好的求每个数的质因数的方法，
    (1)求出每一个数的最小的质因数。
    (2)对每一个算上最小的质因数之后，除一下这个质因数，然后不断变为1。
    
```C++
vector<vector<int>>fac(200010);
vector<int>d(200010);
for(int i = 0 ; i < 200010 ; i++) d[i] = 1;
    for(int i = 200009 ; i >= 2 ; i--){
        for(int j = i ; j < 200010 ; j += i){
            d[j] = i; 
        }
    }
    for(int i = 1; i < 200010 ; i++){
        for(int j = i ; j > 1 ; j /= d[j] ){
            fac[i].push_back(d[j]);
        }
    }
```

AC代码：
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;
const int mod = 998244353;

i64 ksm(i64 a,int b){

    i64 res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1; 
    }
    return res;
}
struct info{

    int to;  i64 a,b;

    info(){};
    info(int to,i64 a,i64 b):to(to),a(a),b(b){};
};

i64 d[200010],f[200010],Max[200010];
vector<vector<int>>fac(200010);
vector<info>v[200010];
i64 ans;
void dfs(int u, int pre){

    for(auto [to, a, b] : v[u]){
        if(to == pre) continue;

        for(auto x : fac[a]) f[x]--;
        for(auto x : fac[b]) f[x]++, Max[x] = max(Max[x], f[x]);
        
        dfs(to, u); 
        
        for(auto x : fac[a]) f[x]++;
        for(auto x : fac[b]) f[x]--;
    }
}
void dfs2(int u,int pre,i64 p){

    ans = (ans + p) % mod;
    i64 tem = p;
    for(auto [to, a, b] : v[u]){
        if(to  == pre) continue;

        p = tem * a % mod * ksm(b, mod - 2) % mod;
        dfs2(to, u, p);
    }
    v[u].clear();
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);
    
    for(int i = 0 ; i < 200010 ; i++) d[i] = 1;
    for(int i = 200009 ; i >= 2 ; i--){
        for(int j = i ; j < 200010 ; j += i){
            d[j] = i; 
        }
    }
    for(int i = 1; i < 200010 ; i++){
        for(int j = i ; j > 1 ; j /= d[j] ){
            fac[i].push_back(d[j]);
        }
    }

    int t;  cin >> t;
    while(t--){
        set<int>s;
        int n;  cin >> n;

        for(int i = 1; i < n ; i++){

            int u, to;  i64 a,b;
            cin >> u >> to >> a >> b;

            for(auto x : fac[a]) s.insert(x);
            for(auto x : fac[b]) s.insert(x);

            v[u].push_back(info(to,b,a));
            v[to].push_back(info(u,a,b));
        }

        dfs(1,0);
        i64 rs = 1;
        for(auto x : s){
            for(int i = 0 ; i < Max[x] ; i++){
                rs = (rs * x) % mod;
            }
            Max[x] = 0; f[x] = 0;
        }
        
        ans = 0;
        dfs2(1, 0, rs);
        cout << ans << endl;

    }
    return 0;
}
```
```diff
!   2022-03-21🚴‍♀️
```
