#   [New Year and Arbitrary Arrangement](https://ac.nowcoder.com/acm/contest/32282/D)


  期望dp，这个题真的tql！！！  
  
  
  首先我们要先知道我们需要转化为什么问题。  
  因为我们在不断地向字符串中加入a, b时，我们得到了一个前缀  
  我们从一个空的字符串，不断增长，在子序列ab的个数超过k时终止。  
  
  那么我们定义dp[i][j]表示，前缀包含i个a，j个ab子序列时的最终期望次数。  
  
  那么我们可以得到的是： dp[i][j] = pa * dp[i + 1][j] + pb * dp[i][i + j]  
  
  (1) 将后面加一个a时，子序列个数不会变，而a的个数加一  
  (2) 将后面加一个b时，子序列的个数加i + j， a 的个数加1  
  
  那么我们的终止状态就是 dp[i][j] (j == k) 而初始状态就是 dp[0][0]  
  
  但是终止的状态有时我们并无法表示出来  
  就比如说现在有很多a，aaaaaaaabaaaaaaaaa但是我们不断地往里面去加a就会使得长度不断变长但是最终的终止状态  
  趋于无穷。  
  
  这时我们发现当 i + j >= k 即表示我们在加入一个b就可以让其满足。  
  
  那么我令此时的dp[i][j]的答案等于 x  
  那么  x = ∑(0 - ∞) B * (j + i + k) * A^k  
  
   我们让两边同时乘以pa并且相减就可以得到：  
   (1 - A) * X = B * (i + j) + B * A / (1 - A)  
   
   又因为1 - A等于B  
   所以：   X = i + j + A / B  
   
   而我们用dp[0][0]表示起始状态其实也不是很对  
   比如说 bbbbbbbbbaaaaaaaab  
   这样再出现第一个a之前出现很多的b其实是没有用的，但是这样的情况有很多，又得统计上  
   于是我们更改起始状态为dp[1][0]  
   因为我们想要想出现至少一个子序列a,b那就说明我们必须先出现一个a，然后再去考虑后面的情况。  
   
   我们算一下概率其实dp[0][0] = dp[1][0]  
   因为我们现在要计算出现第一个a的子序列的概率 
   
    即为：
    = A + B *(A + B * A + B^2 * A + B^3 * A + .......)
    = A + A*(B + B^2 + B^3 + .....)
    = A + A * B * (1 - B^n) / (1 - B)
    = A + A * B / (1 - B)
    又因为1 - B = A
    = A + A * B / A
    = A + B 
    = 1
    
   那么我们就计算出来了dp[1][0] = dp[0][0]  
   
   有两个版本的写法dfs, 和反向dp推，个人觉得dfs版的比较好理解  
ACcode:

```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;
const int mod = 1e9 + 7;

bool vis[1010][1010];
i64 dp[1010][1010], A, B, C, k;

i64 ksm(i64 a, int b){
	
	i64 res = 1;
	while(b){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

i64 dfs(int i, int j){ //dfs版
	
	if(vis[i][j]) return dp[i][j];
	
	if(i + j >= k) return i + j + C;
	
	vis[i][j] = 1;
	return dp[i][j] = (A * dfs(i + 1, j) % mod + B * dfs(i, i + j) % mod) % mod;
	
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	
	i64 pa, pb;  cin >> k >> pa >> pb;
	
	A = pa * ksm(pa + pb, mod - 2) % mod, B = pb * ksm(pa + pb, mod - 2) % mod;
	C = A * ksm(B, mod - 2) % mod;
	
	for(int i = k ; i >= 1 ; i--){ //反向递推版
		for(int j = k ; j >= 0 ; j--){
			if(i + j >= k){
				dp[i][j] = i + j + C;
			} else {
				dp[i][j] = (A * dp[i + 1][j] + B * dp[i][i + j]) % mod;
			}
		}
	}
	cout << dp[1][0] << endl;
//	cout << dfs(1, 0) << endl;
	
	return 0;
}
```
```diff
!   2022-04-19🥣
```
