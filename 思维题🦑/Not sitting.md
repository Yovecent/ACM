:atom:[Not Sitting](https://codeforces.com/contest/1627/problem/B)
=====
    
    我就说嘛，cf第二题就考察算法啦。。。。
    当时情况紧急，没时间多想了，直接往上面写了bfs,奈何整个图的row和col的限制都是1e5，所以单纯的用一个数组就不可以了，
    会直接爆掉，零机一动，改成vector就行了，因为题目保证n*m<=1e5，所以就按需分配内存，妥妥的够，哎，只是这样写这道题就
    太浪费时间了，用了40分钟才完整的AC了这道题。
    
    废话不多说，这道题其实只是一个思维题就可以搞定。
    因为题目中舔狗只想着挨着天菜，所以他选择位置就一定会在有位置的最中间的，因为这样不管天菜选哪个位置，都会保证尽量近，
    而天菜为了远离他，就一定会坐在某一个角落。
    所以我们只需遍历每一个位置，然后求一下那个角落离这个点的位置最远然后就是答案了。
    
AC代码：
===
```C++
/**
*         ✈️author:味增还是倍增
* 	  ⚗️不想做菜鸡呀！！！
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

int n,m;

void solve(){

	vector<int>v;
	for(int i = 1; i <= n ; i++){
		for(int j = 1;j <= m ; j++){
			int x=max(max(i-1+j-1,i-1+m-j),max(n-i+j-1,n-i+m-j));
			v.push_back(x);
		}
	}
	sort(v.begin(),v.end());
	for(int i = 0 ; i < v.size() ; i++){
		printf("%d",v[i]);
		printf("%c",i == v.size()-1?'\n':' ');
	}
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		solve();
	}
	return 0;
}
```
```diff
!    🚛2021-01-16
```
