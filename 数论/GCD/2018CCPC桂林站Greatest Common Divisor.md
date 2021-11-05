# [Greatest Common Divisor](https://vjudge.net/contest/466752#problem/G)


    🥶这道题真的好难，真的是没有思路！！！拉垮了！！！
    
    
    这道题想让我们求出来让所有数都是某个因数的整数倍我们需要让所有数加几次。那么我们假设这个最终要求的的公约数为m
    
    那么我们可以把每一个a[i]都表示成：
    
    k1*m-d  k2*m-d  k3*m-d  k4*m-d ........
    
    所以我们让相邻的做差法。可得
    
    (k1-k2)*m  (k2-k3)*m  (k3-k4)*m ........
    
    所以我们可以让所有相邻的做差法，得到一个新的数组，然后我们如果想要求出来这个m，我们就可以求这个b数组的最大公约数d，那么
    m就是这个d的一个因数，然后再验证每一个因数致使其到达的步数，求出最小值。
    
    这里说明一下，如果 d == 0 就说明，a的所有值都是相同的。因为这样构造出来的b才都是0
    
    其次如果d == 1那就说明没有公约数，也就无解了！！！
    
    这里我们拆因数可以按照质数去拆，就比如说，我们假设如果m==24，那么他的更新步骤在0到23,而3和2都是他的质因数，且更容易到达。所以
    我们只需拆出质数即可。
    
    
    AC代码如下：
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 1e5+10;
const int INF=0x3f3f3f3f;
int a[maxn],b[maxn],n;

int gcd(int a,int b){
    if(!b) return a;
    return gcd(b,a%b);
}
vector<int>v;
void solve(int x){//拆分质因子
    v.clear();
    for(int i = 2 ; i <=x/i ; i++){
        if(x%i==0){
            v.push_back(i);
            while(x%i == 0) x/=i;
        }
    }
    if(x>1) v.push_back(x);
    int Min=INF;
    for(auto x:v){
        int dis=(x-b[1]%x)%x;
        Min=min(Min,dis);
    }printf("%d\n",Min);

}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int t;scanf("%d",&t);int cases=1;
    while(t--){
        int n;scanf("%d",&n);
        for(int i = 1; i <= n ; i++){
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        for(int i = 1; i <= n ; i++){
            b[i]=a[i]-a[i-1];
        }
        printf("Case %d: ",cases++);
        int d=0;
        for(int i = 2; i <= n ; i++){
            d=__gcd(d,b[i]);
        }
        if(d == 0){
            printf("%d\n",b[1]==1);continue;
        }
        if(d == 1){
            printf("-1\n");continue;
        }
        solve(d);
    }
    return 0;
}
```
    
