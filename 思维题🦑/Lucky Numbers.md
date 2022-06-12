#   [Lucky Numbers](https://atcoder.jp/contests/abc255/tasks/abc255_e)

   首先我们根据已给的条件较为简单的可以推出的是：  
   我们假设第一个数为 $a$ , 那么我们剩下的数我们就可以设为：  
   $ S1 - a   $     ,   $S2 - S1 + a$   ,   $S3 - S2 + S1 - a$ ......  
   我们可以把它写成$sum + a$ 或者 $sum - a$  
   
   
   接下来我们就是想要使得更多的数落到我们这些数上面。 
   
   那么我们知道答案一定是上面的至少一种数是X中的数，  
   我们如果假设其中一个数为他恰好是 $xj$
   如果这个数下标是奇数，那他的形式为： $sum + a$
   
   那么此时的a就是 $xj - sum$
   
   否则其形式为： $sum - a$
   那么此时的a就是 $sum - xj$
   
   
   所以我们假设一个数为其中一个数，就可以的出来其成立时a的值，那么对于一个成立的解的话，  
   其一定是相同的a，所以我们只需要将每一个数定一下其是哪一个数，然后计算出相应的a的值，  
   然后让 $cnt[a]++$  
   $cnt[x] = y$  的含义是，当我们取a的值为x时，将会有y个元素恰好是可取的数，正好与我们的求解相同，  
   所以我们只需要统计一下最大的值即可。
   
   
```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;

int main () {
	
	int n, m;
	cin >> n >> m;
	
	vector<int>s(n), x(m + 1);
	
	for (int i = 1; i < n; i++) {
		cin >> s[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> x[i];
	}
	
	vector<i64>cur(n + 1);
	
	for (int i = 1; i < n; i++) {
		cur[i] = s[i] - cur[i - 1];	
	}
	
	map<i64, int> cnt;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i & 1) cnt[x[j] - cur[i]] ++;
			else       cnt[cur[i] - x[j]] ++;
		}
	}
	
	int Max = 0;
	for (auto [val, y] : cnt) Max = max(Max, y);
	
	cout << Max << endl;
	
	return 0;
	
}
```

```diff
!   2022-06-12🐲
```
