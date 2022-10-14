# [D. Assumption is All You Need](https://codeforces.com/gym/103409/problem/D)

  奇奇怪怪的解题方法，只是感觉写的话晕晕糊糊的，构造题好难呀。
  
  首先我们知道的是我们可以交换一对逆序对。
  
  那么对于一个数，我们想让他向后转移的话，说明后面有比他小的数，向前转移的话
  有比他大的数。
  
  我们可以观察到对于一个降序的序列，如果现在要操作的是在第一位上的数，那么这个降序序列上的
  数我们都是可以将其转移到前面，进行一次或者多次交换，这里我们使得其每一次都交换能保证答案最优。
  
  假设现在的序列是：
  
  $10, 9, 5, 3, 2$  
  我们要将5提到前面，那么我们可以得到  
  
  $5, 10, 9, 3, 2$  
  或者  
  $5, 9, 3, 2, 10$  
  
  这样其实保证的是每一位置的数都尽可能的大，其实更准确的说是保证了越往前其值越大。
  这样一定是更优的，因为我们交换时只能向后交换，那么我们构造的降序序列越长就使得我们的选择越多，
  则即保证了最优。
  
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 2e4 + 10, M = 5e3 + 10;

int a[maxn], b[maxn];

int main () {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int t;
	scanf("%d", &t);
	while (t--) {

		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]);

		bool ok = true;
		vector<pair<int, int> > cur;
		for (int i = 1; i <= n; i++) {

			if (a[i] < b[i]) {
				ok = false;
				break;
			}

			int j = i + 1;
			while (a[i] != b[i]) {
				if (a[i] >= a[j] && a[j] >= b[i]) {
					cur.push_back({i, j});
					swap(a[i], a[j]);
				}
				j++;
			}
		}

		if (ok) {
			printf("%d\n", cur.size());
			for (auto val : cur) {
				int x = val.first, y = val.second;
				printf("%d %d\n",x, y);
			}
		} else {
			printf("-1\n");
		}
	}

	return 0;
}

```

```diff
!   🐿️2022-10-14
```
  
  
  
