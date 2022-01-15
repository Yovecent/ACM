🚡[Mining a](https://codeforces.com/gym/102460)
=======
```diff    
    🐡对于异或⊕还是不太熟悉，最基本的性质都不知道。
    
!   这道题用到的性质是 c = a ⊕ b ，那么 a = c ⊕ b
    
    对于原式，我么可以假设x = a⊕b , y=b，
    那么我们现在的任务就是求出下x,y然后异或求取最大值。
    
    我们对式子展开并进行十字分解可化成：(尽量往十字相乘去化简，这样才能有效地求出各个变量之间的关系)
    
    (x-n)*(y-n) = n*n
    
    我们可以假设y = n+k,那么x = (n^2)/k+n;
    所以我们现在遍历k的取值，因为x,y都是整数，所以就是(n^2) % k == 0，所以k 的取值就在1~n之间。
    又因为这道题的限时是2s所以是可以的。
    
```
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <queue>

#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
const int maxn  = 1e3+10;
const int mod = 1e9+7;

int n;
void solve(){

	ll ans=0;
	for(int i = 1; i <= n ; i++){
		if((1ll*n*n) % i != 0 )continue;
		ll x = 1ll*n*n/i+n;
		ll y =n+i;
		ans=max(ans,x^y);
	}printf("%lld\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		solve();
	}
	return 0;
}
```
```diff
!    🏑2021-01-15 
```
