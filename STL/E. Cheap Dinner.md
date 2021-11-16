# [E. Cheap Dinner](https://codeforces.com/contest/1487/problem/E)

    🏸再一次感受到了数据结构的强大!!!(代码思路来源于榜一大哥)
    
    这道题猛地看上去像是分组背包，加上依赖性背包。但是却难以下手!!!
    
    首先观察题目给出的m，及其代表的含义，表示这一组与上一组中某对元素不能在一起。那就是说，只要我们采用按顺序的方法，
    也就是先选第一个然后选第二个，我们就只用在第一组中合法的转化形式，挑出不存在与本元素冲突的，最小的方案。
    因为第三组和第一组并没有关系，而只与第二组有关系。所以我们在对第二组的元素进行构造时，只考虑当前一个元素的冲突限制即可构成的背包。
    
##  对于set的巧妙使用  
  
   🏹我们来考虑一下对于当前元素，我们要找到一个最小的背包，并且其中不含与之冲突的元素。
   
   对于最小我们想到了排序，那么很多数据结构都是可以进行自动排序的，比如说map,set，
   我们就可以用set来存储当前构成的背包 set<PII> 第一元素就是背包重量，第二个是构成这个背包的元素下标。
  
   🩹同时我们还要验证是否和这个元素冲突，所以那无非就是看这个元素是否是和第i行第j列元素冲突的元素。
  
   所以我们又可以开一个set用vector<set<int>> 来对每一行每一个元素都开一个，来存与之冲突的元素，验证时我们只需要判断
   set.count(x)是否存在即可。
 
```C++
  #include <iostream>
#include <cstdio>
#include <vector>
#include <set>

#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,int>PII;
const int maxn = 2e5+10;

int n[5],grp[5][maxn];
void solve(){

    for(int i = 1; i <= 4 ; i++){
        scanf("%d",&n[i]);
    }
    for(int i = 1; i <= 4 ; i++){
        for(int j = 1; j <= n[i] ; j++){
            scanf("%d",&grp[i][j]);
        }
    }
    vector<set<int>>v[5];
    for(int i = 2; i <= 4; i++){
        v[i]=vector<set<int>>(n[i]+1);
        int k;scanf("%d",&k);
        for(int j = 1; j <= k ; j++){
            int a,b;scanf("%d %d",&a,&b);
            v[i][b].insert(a);
        }
    }
    set<PII>cost[5];
    for(int i = 1; i <= n[1] ; i++) cost[1].insert({grp[1][i],i});
    for(int i = 2; i <= 4 ; i++){
        for(int j = 1; j <= n[i] ; j++){
            auto x=cost[i-1].begin();
            while(x!=cost[i-1].end() && v[i][j].count(x->se)) x++;
            if(x!=cost[i-1].end()) cost[i].insert({grp[i][j]+x->fi,j});
        }
    }
    if(!cost[4].size()) printf("-1\n");
    else                printf("%lld\n",cost[4].begin()->fi);

}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    solve();
    return 0;
}
```
