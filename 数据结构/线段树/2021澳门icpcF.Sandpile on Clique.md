#  [2021澳门icpcF.Sandpile on Clique](https://ac.nowcoder.com/acm/contest/31454/F)


    当时zjl姐姐口胡的循环次数不会超过n次，我当时因为没有推出来，并且觉得有点离谱就没有往那方面去想，
    结果答案就是那样的。
    
    
    首先我们需要知道循环次数不会超过n次。
    我们假设循环n次之后
    我们现在只需要验证大于n - 1, n - 2, n -3, n -4 ,....0的至少有一个数，且他们是分别属于这些集合的。
    
    这样的话，我们选择n - 1的数去拆分，就会把后面的数都加1，然后n - 1变为0，就又变成了之前的数组于是就会无限重复下去。
    
    我们像一个极端的情况，就是每个点都向外面扩展了1次，那么每个点都是n - 1，而这个集合肯定是满足上面的要求的，因为n - 1是大于
    n - 2, n -3, n -4....
    那么我们再想一下一般情况。
    
    也就是说可能会有点超过1次的，那么就会使得一个点变成n - 2, 一个点变成n
    也就是说我们没让一个点多一次的话，就会让一个小于n的数加1，而就相当于我们每次让一个数往后倒退就会让一个数向前前进，
    就相当于他们在不断地顶替位置。所以一定是可以的。
    
    
    那么我们现在的任务就变成了进行n轮，查询一下此时数组中有那个位置的数大于等于n - 1，然后将它进行一次扩展，
    也就是将他减n - 1，其他数都加1。
    
    也不就是查询区间最大值的线段树吗？(区间修改，类单点查询)
    
    这里需要懒标记了。
    
    同时query函数也有一些不一样，我们需要知道大于等于n - 1的位置，将他变一下。
    
    那么我们的查询点的函数似乎就得再多设置一个了，其实不用了，我们可以用一个差分数组，最后输出差分数组和a的值的和就可以了。
    
ACcode:    
```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;
const int maxn =  5e5 + 10;

int a[maxn], b[maxn];
int n;
struct segmentTree{
	
	int info[maxn << 2], lazy[maxn << 2];
	void pushup(int p){
		info[p] = max(info[p << 1], info[p << 1 | 1]);
	} 
	void pushdown(int  p){
		if(lazy[p] != 0){
			info[p << 1] += lazy[p];
			info[p << 1 | 1] += lazy[p];
			lazy[p << 1] += lazy[p];
			lazy[p << 1 | 1] += lazy[p];
			lazy[p] = 0;
		} 
	}
	void build(int p, int l, int r){
		if(l == r){
			info[p] = a[l];
			return ;
		}
		int mid =  l + r >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		pushup(p);
	}
	void update(int p, int l, int r, int L, int R, int x){
		if(L > R) return;
		if(l >= L && r <= R){
			info[p] += x;
			lazy[p] += x;
			return;
		}
		pushdown(p);
		int mid = l + r >> 1;
		if(L <= mid) update(p << 1, l, mid, L, R, x);
		if(R > mid) update(p << 1 | 1, mid + 1, r, L, R, x);
		pushup(p);
	}
	int query(int p, int l, int r){
		if(info[p] < n - 1) return -1;
		if(l == r) return l;
		pushdown(p);
		int mid = l + r >> 1;
		if(info[p << 1] >= n - 1) return query(p << 1, l, mid);
		else return query(p << 1 | 1, mid + 1, r);
	}
}tree;
int main()
{
	ios::sync_with_stdio(false);  cin.tie(0);
	
	cin >> n;
	for(int i = 1 ; i <= n ;i++)  cin >> a[i];
	
	tree.build(1, 1, n);
	for(int i = 1 ; i <= n ; i++){
		int pos = tree.query(1, 1, n);
		if(pos == -1) break;

		tree.update(1, 1, n, 1, pos - 1, 1);
		tree.update(1, 1, n, pos + 1, n, 1);
		tree.update(1, 1, n, pos, pos, 1 - n);
		b[1] += 1, b[pos] -= 1, b[pos + 1] += 1, b[pos] -= (n - 1), b[pos + 1] += (n - 1);
	}
	if(tree.query(1, 1, n) == -1){
		for(int i = 1; i <= n ; i++){
			b[i] += b[i - 1];
			cout << a[i] + b[i];
			if(i != n) cout << " ";
			else           cout << endl;
		}
	} else {
		cout << "Recurrent" << endl;
	}
	return 0;
}
```
```diff
!    2022-04-16🩰
```
