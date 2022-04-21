#   [D. Optimal Partition](https://codeforces.com/contest/1668/problem/D)


   题中的条件是：
   如果这一段的区间的求和大于0那就等于正的区间长度
   如果这一段的区间求和等于0，那就说明其等于0
   如果这一段的区间长度小于0，那就等于负的区间长度
   
   当时的想法是将正的点合并，然后考虑其间负的值加到那一边，但是怎么想也不会。
   
   这里的dp还是从前往后的。
   
   首先dp[i]的含义就是从 1 - i的最优解的值。
   
   那么我们对于当前i的值的更新，
   就可以枚举j (1 <= j < i)
   然后拿j的值去更新 i 
   其中状态转移是
   
   dp[i] = dp[j] + (i - j) (s[i] > s[j])
   dp[i] = dp[j] (s[i] == s[j])
   dp[i] = dp[j] - (i - j)  (s[i] < s[j])
   
   但是这样的话我们就是一个O(n²)的算法了并不能通过
   
   所以我们得优化一下：
   
   将其移一下位置：
   dp[i] = (dp[j] - j) + i
   dp[i] = dp[j]
   dp[i] = (dp[j] + j) - i
   
   对于当前这个i，前面的所有的j我们都可以按照前缀和划分为3类，那么我们其实就可以去这三种情况中找到最大的
   然后去更新就可以了。
   所以我们可以建3颗线段树，
   对于每一颗线段树其叶子节点的值都为一种前缀和，那么我们只需要将前缀和离散化，然后
   不断地更新点。
   
ACcode:
```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;
const int maxn = 5e5 + 10, INF = 0x3f3f3f3f;

int b[1000000], dp[1000000], cnt;

struct Segment_Tree{
	
	int info[maxn << 2][3];
	
	void build(int p, int l, int r){
		if(l == r){
			for(int i = 0 ; i < 3 ; i++) info[p][i] = -INF;
			return;
		} 
		int mid = l + r >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		for(int i = 0 ; i < 3 ; i++) info[p][i] = -INF;
	}
	void update(int p, int l, int r,int x, int val, int k){

		if(l == r){
			info[p][k] = max(info[p][k], val);
			return;
		}
		int mid = l + r >> 1;
		if(x <= mid) update(p << 1, l, mid, x, val, k);
		else         update(p << 1 | 1, mid + 1, r, x, val, k);
		info[p][k] = max(info[p << 1][k], info[p << 1 | 1][k]);
	}
	int query(int p, int l, int r, int L, int R, int k){

		if(L > R) return -INF;
		if(l >= L && r <= R){
			return info[p][k];
		}
		int mid = l + r >> 1, res = -INF;
		if(L <= mid ) res = max(res, query(p << 1, l, mid, L, R, k));
		if(R > mid) res = max(res, query(p << 1 | 1, mid + 1, r, L, R, k)); 
		return res;
	}
}tree;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
		
	int t;  cin >> t;
	while(t--){
		int n;  cin >> n;
		vector<i64>a(n + 1), sum(n + 1), v(1);
		for(int i = 1 ; i <= n ; i++){
			cin >> a[i];
			sum[i] = sum[i - 1] + a[i];
			v.push_back(sum[i]);
		}
	
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for(int i = 0; i <= n ; i++){
			b[i] = lower_bound(v.begin(), v.end(), sum[i]) - v.begin() + 1;
		}
		
		int m = v.size();
		tree.build(1, 1, m);
		for(int i = 0 ; i < 3 ; i++) tree.update(1, 1, m, b[0], 0, i);
		for(int i = 1; i <= n ; i++){
			
			dp[i] = tree.query(1, 1, m, 1, b[i] - 1, 0) + i;
			dp[i] = max(dp[i], tree.query(1, 1, m, b[i], b[i], 1));
			dp[i] = max(dp[i], tree.query(1, 1, m, b[i] + 1, m, 2) - i);
			
			tree.update(1, 1, m, b[i], dp[i] - i, 0);
			tree.update(1, 1, m, b[i], dp[i], 1);
			tree.update(1, 1, m, b[i], dp[i] + i, 2);
		}
		
		cout << dp[n] << endl;
	}
	return 0;
}


```
   
   
+   但是其实我们只用考虑第一种情况就可以了，为啥子呢？

###  (1) 对于dp[i] = dp[j] - (i - j)  (s[i] < s[j])

    我们想一下如果是这样的话，那就是说从 j + 1 ~ i的这段区间每个点的贡献都是-1
    那我们直接用dp[i - 1] 然后让i处的值单独为一个区间 去更新dp[i]的话一不会差于这种情况
    即 ： dp[i] = dp[i - 1] + (a[i] > 0 ? 1 : ((a[i] < 0) ? -1 : 0));
   
   
### (2) 对于dp[i] = dp[j]

    这样的话那就是说从 j + 1 ~ i 的这段区间的和为0
    那么我们可以推理出的是我们将这个区间拆分的结果一定不会差于这一整段的区间合并。
    
    首先这一区间合并的答案为0
    
    1.当区间长度为偶数时。
    那么我们将其拆分成两端相同的区间，那么答案是不会变的。
    因为一边为 正的， 那另一边就为负的相加又消了。  而都为0也使得答案不会变。
    
    2.当区间长度为奇数时
    我们考虑擦划分成 (n - 1) / 2 与 (n + 1) / 2(左右不定)
    如果(n - 1) / 2的那部分为负数，那就说明(n + 1) / 2的那段为正数，所以会使得答案变大
    (n - 1) / 2的那部分为0，那就说明(n + 1) / 2的那段也为0，所以会使得答案不变。
    
    否则我们再拆分为
    (n - 1) / 2, 1, (n - 1) / 2
    此时 (n - 1) / 2 都是为非负数，
    那么如果(n - 1) / 2均为0，那中间那位也为0， 答案不变
    
    如果两个都为正数，那么答案就一定会增大。
    
    所以拆分比不拆分要好。
    同时我们需要考虑长度为1的时候， 那就一定是整段加进去了。
    所以还是上面的那个语句更新一下:
    dp[i] = dp[i - 1] + (a[i] > 0 ? 1 : ((a[i] < 0) ? -1 : 0));
    
ACcode：
```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;
const int maxn = 5e5 + 10, INF = 0x3f3f3f3f;

int b[1000000], dp[1000000], cnt, tr[1000000];

int lowbit(int x){ return x & -x;}
void update(int p, int x, int m){
	
	while(p <= m){
		tr[p] = max(tr[p], x);
		p += lowbit(p);
	}
}

int query(int p){
	int x = -INF;
	while(p){
		x = max(x, tr[p]);
		p -= lowbit(p);
	}
	return x;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
		
	int t;  cin >> t;
	while(t--){
		int n;  cin >> n;
		vector<i64>a(n + 1), sum(n + 1), v(1);
		for(int i = 1 ; i <= n ; i++){
			cin >> a[i];
			sum[i] = sum[i - 1] + a[i];
			v.push_back(sum[i]);
		}
	
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for(int i = 0; i <= n ; i++){
			b[i] = lower_bound(v.begin(), v.end(), sum[i]) - v.begin() + 1;
		}
		
		int m = v.size();
		for(int i = 1 ; i <= m ; i++) tr[i] = -INF;
		update(b[0], 0, m);
		
		for(int i = 1; i <= n ; i++){
			dp[i] = dp[i - 1] + (a[i] > 0 ? 1 : ((a[i] < 0) ? -1 : 0));
			
			dp[i] = max(dp[i], query(b[i] - 1) + i);
			
			update(b[i], dp[i] - i, m);
		} 
		cout << dp[n] << endl;

	}
	return 0;
}

```
```diff
!   2022-04-21💐
```
   
