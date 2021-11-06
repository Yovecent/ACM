# [Color a Tree](http://poj.org/problem?id=2054)& [2018 China Collegiate Programming Contest - Guilin Site A. Array Merge ](https://codeforces.com/gym/102823/problem/A)

    这两道题属于同类型的题目，考察了贪心，好难啊！！！！
    
    🍡首先先看桂林站的题目。
    对于两个序列A和B，我们要在不改变其相对位置的前提下，不断的插入形成一个新的数组，而我们要满足的是让C[i]*i的总和尽可能的小。
    
    首先这道题如果两个序列都已从小到大排列，那么就是一道简单的贪心，我们可以设置两个指针，从前往后，尽可能取大的。但是没有排好序的话，
    这样做就是错误的，因为对于一个序列如果有很大的数被排到了后面的话，就会因为这一个小的数而无法及时的排到前面。
    
    我们来考虑一下，如果我们先按照正确的方式随便排成一个序列，我们让他们交换位置而使得这个序列代价变小。我们考虑交换相邻的，那么交换的
    总是一段a和一段b，即使只有一个我们也视为一段。
    对于这样两段，我们给出如下证明：  
    
    
![IMG_20211106_181021_edit_112554215447407](https://user-images.githubusercontent.com/92497177/140606040-907d4118-b15f-4181-ba61-a0f709b7c0f9.jpg)
    所以说如果想要交换之后使得费用更小，就需要让平均值更大的去到前面。
    
    所以我们可以把序列a,b都分成一段一段的尽可能的让a,b的平均值更大，分成之后就如同最开始的那样，把一段看成一个连通块，还是还是用一个双指针，把大的排到前面。
    
    
    所以我们现在的目标就是怎么分，因为我们要他们的平均值尽可能的大，那么我们从后往前遍历，如果当前这个连通块加到前面的连通块之后能够使其平均值更大那就合并。
    
   
   以下是AC代码：
```C++
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6+10;

ll dp[maxn][2];
int len[maxn][2],a[maxn],b[maxn];
int cnt=0;ll sum;
struct node{

    int len,id,po;
    ll sum;
    friend bool operator<(node x,node y){
        if(x.po != y.po) return x.sum*y.len>y.sum*x.len;
        return x.id <y.id;
    }
}p[maxn];
int n,m;
vector<int>v[maxn],v1[maxn];
void init(){

    cnt=0;sum=0;
    for(int i = 1; i <= n ; i++){
        scanf("%lld",&dp[i][0]);len[i][0]=1;
        v[i].clear();v[i].push_back(i);
        a[i]=dp[i][0];
    }
    for(int i = 1; i <= m ; i++){
        scanf("%lld",&dp[i][1]);len[i][1]=1;
        v1[i].clear();v1[i].push_back(i);
        b[i]=dp[i][1];
    }
}
void init_pre(int po){

    bool f=true;int k;
    int l = po == 0?n:m;
    while(f){
        f=false;
        for(int i = l; i >= 1; i--) if(dp[i][po]) {k=i;break;}
        for(int i = k-1; i >= 1 ; i--){
            if(dp[i][po]){
                if(dp[i][po]*len[k][po] < dp[k][po]*len[i][po]){
                    dp[i][po]+=dp[k][po];dp[k][po]=0;
                    len[i][po]+=len[k][po];len[k][po]=0;
                    if(po == 0){
                        for(int j = 0 ; j < v[k].size() ; j++){
                            v[i].push_back(v[k][j]);
                        }v[k].clear();
                    }
                    else{
                        for(int j = 0 ; j < v1[k].size() ; j++){
                            v1[i].push_back(v1[k][j]);
                        }v1[k].clear();
                    }
                    f=true;
                }
                k=i;
            }
        }
    }
}
void pre(){

    for(int i = 1; i <= max(m,n) ; i++){
        if(i <= n){
            if(dp[i][0]){
                p[cnt].sum=dp[i][0];p[cnt].len=len[i][0];
                p[cnt].id=i;p[cnt++].po=0;
            }
        }
        if(i <= m){
            if(dp[i][1]){
                p[cnt].sum=dp[i][1];p[cnt].len=len[i][1];
                p[cnt].id=i;p[cnt++].po=1;
            }
        }
    }
    sort(p,p+cnt);
}
void solve(){
    int k=1;
    for(int i = 0 ; i < cnt ; i++){
        int x=p[i].id;
        if(p[i].po  == 0){
            for(auto t : v[x]){
                sum+=1ll*(k++)*a[t];
            }
        }
        else{
            for(auto t:v1[x]){
                sum+=1ll*(k++)*b[t];
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
    int t;scanf("%d",&t);int cases=1;
    while(t--){
        scanf("%d %d",&n,&m);init();
        init_pre(0),init_pre(1);
        pre();
        solve();printf("Case %d: %lld\n",cases++,sum);
    }
    return 0;
}
```


    然后就是对树上的点进行染色
