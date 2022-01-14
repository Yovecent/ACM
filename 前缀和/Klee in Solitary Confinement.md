🗾[Klee in Solitary Confinement](https://codeforces.com/gym/103470/problem/C)
====
    🦢这道题打南京的一道被卡住的题，现在想想只是一个单纯的思维题，还是太菜了。
    
    首先我们需要知道是，对于这个序列我们需要考虑的只有x 与 x+k两个数。
    我们把除了x与x+k的数都删除之后保留剩下的元素。
    
    设sum[i][0]表示在i位置前x的个数，sum[i][1]表示在i位置前x+k的元素的个数
    现在我们假设把区间[l,r]内的元素加序列长度为n，那么我们统计x+k此时的个数：
    
    (sum[r][0] - sum[l-1][0]) + sum[n][1] - (sum[r][1]-sum[l-1][1])
        🩹[l,r]内x的个数              🩹[l,r]以外的x+k的个数
        
    整理可得：
    sum[n][1] + (sum[l-1][1]-sum[l-1][0]) + (sum[r][0]-sum[r][1])
    即为从前往后遍历，记录一个左端点的最大值，然后不断的更新右端点找出此时的最大值。’
    
    整体思路不难，但是当时就是想不出来呀！！！！
    
AC代码：
===
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef  long long ll;
const int maxn = 4e6+10;
const int opt = 2e6;
const int INF = 0x3f3f3f3f;

int n,k;
vector<int>v[maxn];
int sum[maxn][2];

void solve(){

    int ans=0;
    for(int j = 0 ; j < maxn ; j++){
        if(!v[j].size()) continue;
        int Max1=-INF,Max2=0;
        for(int i = 0 ; i < v[j].size() ; i++){
            sum[i][0]=sum[i-1][0]+(v[j][i]==j);
            sum[i][1]=sum[i-1][1]+(v[j][i]!=j);
        }
        int cnt=sum[v[j].size()-1][1];
        int tem=-INF;
        for(int i = 0 ; i < v[j].size() ; i++){
            tem = max(tem,sum[i-1][1]-sum[i-1][0]);
            ans = max(ans,cnt+tem+sum[i][0]-sum[i][1]);
        }
    }
    printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    scanf("%d %d",&n,&k);
    int Max=0;
    for(int i = 1; i <= n ; i++){
        int x;scanf("%d",&x);x+=opt;
        v[x].push_back(x);v[x-k].push_back(x);
        Max=max(Max,(int)v[x].size());
    }
    if(!k){
        printf("%d\n",Max/2);
    }
    else  solve();
	return 0;
}
```
```diff
!     💥2021-01-15
```
