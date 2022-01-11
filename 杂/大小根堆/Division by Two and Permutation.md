⚔️Division by Two and Permutation
=====
    咱就是说这道题真的是开了眼了，巧妙地利用了大根堆。
    
    因为我们在将它们不断除以2的过程中，他们会趋于 1~n这个区间内，当时我就在想我把一个数除尽了，看一下能覆盖
    哪一些，然后找出一组合法的构成，但这样似乎就要用到了dfs，而且时间上也不允许。
    我们换一种思想，因为我们想要构成1~n这n个数，所以对于每一个数必须至少有一个数会在变化过程中经过这个数，那么
    我们不断地将他们除以2，保证每次都让当前最大的除以2，也就是说不断的降低上界，然后对于当前这个需要的数，如果恰好
    有至少一个，我们随便拿出来一个就可以了，因为现在他们都是等价的，就是这个动态的过程，便可以实现。
    
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstring>
#include <queue>

using namespace std;

typedef long long ll; 
const int maxn = 1e5+10;
const int INF = 0x3f3f3f3f;

int vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<int>q;
		int n;scanf("%d",&n);
		for(int i = 1; i <= n ; i++){
			int x;scanf("%d",&x);q.push(x);
			vis[i]=0;
		}
		while(q.size()){
			int x=q.top();q.pop();
			if(x > n){
				q.push(x/2);
			}
			else if(vis[x]){
				if(x/2 > 0) q.push(x/2);
			}
			else{
				vis[x]=1;
			}
		}bool f=true;
		for(int i = 1; i <= n ; i++){
			if(!vis[i]){
				f=false;break;
			}
		}
		if(f)  printf("YES\n");
		else   printf("NO\n");
	}
	return 0;
}
```
