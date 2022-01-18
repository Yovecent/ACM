🌗[J. Xingqiu's Joke](https://codeforces.com/gym/103470/problem/J)
====
    
    区域赛的真的都好难啊，开拓新思想啦！！！
    
    首先我们考虑a,b的差值： a - b = c
    那么如果存在一个质因数x的那么他也是c的因数。
    因为：k1*x-k2*x=k3*x
    所以我们利用除法转移的话，其实就是从c的质因数去选择。
    所以我们可以定义f[a][c]  c,代表了他们差值，并且在a,b同增同减的时候c的值是不变的。
    我们对于一个状态的转移就是对其除以c的质因数，并且考虑到向上取整以及向下取整，所以f[a][c]可以由
    f[a/g+1][c/g] 或 f[a/g][c/g]转移而来，所以我们可以取一个最小值。
    又因为我们每次选择的是他除以哪一个质因数，所以即为质因数级别的dfs。
    
    又因为2*3*5*7*11*13*17*19*23*29会超过最大的c，即质因数最多只有8个，那么dfs就妥妥的了。
    
    这个map的键不能设置成pair类型，所以我们可以利用哈希的方法，因为最大值为1e9所以让a*1e9+c就可以了，同时我们只是想要标记，
    并不用排序，所以设成unordered_map即可。
    
```C++
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
unordered_map<ll,int>m;
vector<int>v;

ll Hash(int a,int b){

    return 1ll*a*1e9+b;
}
int dfs(int a,int c){
    if(a == 1) return 0;
    if(c == 1) return a-1;
    if(m[Hash(a,c)]) return m[Hash(a,c)];
    int Min=a-1;
    for(auto x : v){
        if(c%x == 0){
            int res=a%x;
            Min=min({Min,res+1+dfs(a/x,c/x),x-res+1+dfs(a/x+1,c/x)});
        }
    }
    return m[Hash(a,c)] = Min;
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    int t;scanf("%d",&t);
    while(t--){
        v.clear();m.clear();
        int a,b;scanf("%d %d",&a,&b);
        if(a>b)swap(a,b);
        int c=b-a;
        if(c == 0){
            printf("%d\n",a-1);continue;
        }
        int x=c;
        for(int i = 2; i*i <= x ; i++){
            if(x%i == 0) v.push_back(i);
            while(x%i==0) x/=i;
        }
        if(x!=1) v.push_back(x);
        printf("%d\n",dfs(a,c));
    }
    return 0;
}
```
```diff
!     🧩2021-01-18    
```
