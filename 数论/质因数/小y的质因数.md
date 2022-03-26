#  🌇[小y的质因数](https://ac.nowcoder.com/acm/contest/30880/E)

    
    我们考虑这个公式，设数x的质因数为cnt
    log2(x) - k <= cnt
    log2(x) - cnt <= k
    
    因为log2(x) 与 cnt 都是定的，及对不同的数进行了分类，所以我们求对于不同的k的时候就可以很方便
    
    所以我们就把每一个数按照log2(x) - cnt 去分类
    首先我们考虑一个数最多的质因子的个数即为假设都为2,所以一共有log2(x)个质数
    那么如果log2(x) - cnt <= 10
    那么我们把其中11个2合并为1个数2048达到最大的两数之差，所以我们用到的质数不会超过2048
    
    
    那么我们先筛出质数，然后再使用dfs对数进行分类。
    
    dfs中我们定义dfs(枚举到第几个质数p，当前这个数x，数含有的质数的个数num)
    剪枝就是log2(x) - num > 10
    时间复杂度不会求呀。。。。
    这里的log是向上取整
    
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;

vector<int>fac;
vector<i64>ans[11];
vector<bool>vis(2050);

void init(){

    for(int i = 2; i <= 2048 ; i++){
        if(!vis[i]) fac.push_back(i);
        for(int j = 0 ; i * fac[j] <= 2048  && j < fac.size() ; j++){
            vis[i * fac[j]] = true;
            if(i % fac[j] == 0) break;
        }
    } 
}

int Q(i64 x){

    int a = __builtin_ctzll(x);
    int b = __builtin_clzll(x);
    int c = 64 - __builtin_clzll(x) - 1;
    if(a + b + 1 < 64){
        return c + 1;
    } else {
        return c;
    }
}
void dfs(int p, i64 x, int num){

    if(Q(x) - num > 10 || x > 1e12) return;
    ans[Q(x) - num].push_back(x);

    for(int i = p ; x <= 1e12 / fac[i] && i < fac.size() ; i++){
        dfs(i, x * fac[i], num + 1);
    }

}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);
    
    init();
    dfs(0, 1, 0);

    for(int i = 0 ; i <= 10 ; i++) sort(ans[i].begin(), ans[i].end());

    int t;  cin >> t;
    while(t--){
        i64 l, r;  int k;
        cin >> l >> r >> k;

        i64 cnt = 0;
        for(int i = 0 ; i <= k ; i++){
            cnt += upper_bound(ans[i].begin(), ans[i].end(), r) - lower_bound(ans[i].begin(), ans[i].end(), l);
        }
        cout << cnt << endl;
    }
    return 0;
}
```
```diff
!    2022-03-26🔌
```
