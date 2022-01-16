⚔️[Road Optimization](https://codeforces.com/contest/1625/problem/C)
====
    这道题n的范围很小，可以直接3重dp搞起来，贪心贪了半天(难受)
    
    😰但是本小菜鸡并不会dp，练的太少了，这么简单的都不会(QWQ)
    
    
    🧮这道题的思路来自sjjj。
    
    首先定义dp[i][j]表示在前i位中，我删除了j位
    
    那么我们可一利用三重循环
    首先外层是从1~n，但这样还是不够的，因为还有终点，所以加一位至n+1,而使d[n+1]=l
    然后第二层枚举我要删除的个数，从0到k
    第三层即使状态转化，
    
    我们考虑一下转移方程:dp[i][j]可以表示成min(dp[i][j],dp[i-1][j],dp[i-2][j-1]+a[i-2]*(d[i]-d[i-2]),dp[i-3][j-2]+a[i-3]*(d[i]-d[i-3]),......)
    
    意思就是说，我如果想要删除j位的话，我可以从dp[i-1][j]转化来，又因为dp[i-1][j]不能删除第i-1位，所以还是删除j位，
    从i-2转移过来的话，说明我删除了第i-1位，那么就还需要再删除j-1位，即dp[i-1][j-1]
    
    
    所以第三层即为循环可以删除几位，及从i-p转移过来。
    
    同时我们知道dp[1][?]都是0，因为现在我们还没出发。
    
AC代码：
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 5e2+10;
const int INF = 0x3f3f3f3f;

int dp[maxn][maxn];
int d[maxn],a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
	int n,l,k;scanf("%d %d %d",&n,&l,&k);
	for(int i = 1; i <= n ; i++) scanf("%d",&d[i]);
	for(int i = 1; i <= n ; i++) scanf("%d",&a[i]);
	d[n+1]=l;
	for(int i = 2; i <= n+1; i++){
		for(int j = 0 ;j <= k ;j++){
			dp[i][j]=INF;
			for(int p = 1; p < i ; p++){
				if(j-p+1>=0) dp[i][j]=min(dp[i][j],dp[i-p][j-p+1]+a[i-p]*(d[i]-d[i-p]));
			}
		}
	}
	int Min = INF;
	for(int i = 0 ; i <=k ; i++) Min=min(Min,dp[n+1][i]);
	printf("%d\n",Min);
	return 0;
}
```
```diff
!      🏃2021-01-12
```
