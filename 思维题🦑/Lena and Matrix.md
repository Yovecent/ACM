#  [Lena and Matrix](https://codeforces.com/contest/1689/problem/D)


   真心的感觉思维题是一种十分优雅，美妙的题，见到的每一次都是一次邂逅。
   
   
   首先曼哈顿距离是  $|x - a| + |y - b| $
   
   我们想对于给定的一个曼哈顿距离，我们找出其曼哈顿距离相同的点：
   
![image](https://user-images.githubusercontent.com/92497177/173234167-b6fea97b-5811-4181-b33c-3f998a6cc24d.png)
   即为一个菱形，对于其四条边其分别为
   y = x + b1, y = -x + b2, y = x + b3, y = -x + b4
   
  对于一个给定的中心，这是他最大的覆盖范围，所以我们如果想要将这个区间最大化，那么我们就是要求出这四条边最远的距离。
  
  对于1号边，我们是想要将b1最大化，所以求的是$(y - x)$最大值
  同理对于2号边，是$(x + y)$ 的最大值
  3号边是$(y - x)$的最小值
  4号边是$(x + y)$的最小值
  
  所以我们只需要求出这四个极限的点，然后遍历所有的点去找出使得答案最小的即可。


```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;


char s[1001][1001];


int main () {
	ios::sync_with_stdio(false);cin.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		
		int n, m;
		cin >> n >> m;
		
		pair<int,int> a = {1, 1}, b = {n, m}, c = {1, m}, d = {n, 1};
		
		for (int i = 1; i <= n ; i++) {
			
			cin >> s[i] + 1;
			for (int j = 1; j <= m; j++) {
				if (s[i][j] == 'W') continue;
				if (i + j > a.first + a.second) a = {i, j};
				if (-(i + j) > -(b.first + b.second)) b = {i, j};
				if ((i - j) > c.first - c.second) c = {i, j};
				if ((j - i) > d.second - d.first) d = {i, j};
			}
		}
		
		vector<pair<int,int> > di;
		di.push_back(a),  di.push_back(b),  di.push_back(c),  di.push_back(d);
		
		
		pair<int,int> ans = {1, 1};
		int Min = 0;
		for (auto [x, y] : di) Min = max(Min, abs(1 - x) + abs(1 - y));
		 
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int tem = 0;
				
				for (auto [x, y] : di)  tem = max(tem, abs(i - x) + abs(j - y));
				
				if (tem < Min) {
					Min = tem;
					ans = {i, j};
				}
			}
		}
		
		cout << ans.first << " " << ans.second << endl;
	}
	return 0;
}

```

```diff
!   2022-06-12🛁
```
