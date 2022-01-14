⚔️[D - Paimon Sorting](https://codeforces.com/gym/103470)
===
    🎣咱就是说，这应该有史以来做的最久的一道题了吧。呜呜。。。
  
    首先需要知道的是求什么Ak指的是，就可以认为是我把这个前缀A1~Ak取出来，然后按题中给出的算法去求一下总的交换次数，
    所以答案是输出了n个数。
  
    同时对于1来说答案永远是0，因为他不用交换。
  
    然后我们就来考虑这道题的精髓了。
  
    首先我们可以把这里面的数分为两类，一类叫特殊元素，另一类叫非特殊元素。
    特殊元素指的是凡是在第一轮交换过位置的元素，并且通过观察我们可以知道，把这些元素取出来之后，现在位于第一位
    的元素是整个序列的最大值（原序列），后面的每个元素都是满足递增的。我们把这些数命名为p,
    那么经过第一轮交换之后现在式子就是
    C1  A2 A3 C4 A5 C6.......
    然后第二轮往后的交换次数都是有规律的：
    对于每一元素，其交换次数的贡献值都是在本元素之前已经出现的大于他的元素的个数，于是我们就可以动态的
    进行第一轮的交换然后求出每一位的贡献值。
    并且对于非特殊元素，他的贡献值就是已经出现的大于他的元素的个数，而特殊元素的交换次数都是2。
    至于为什么特殊元素的交换次数是2，因为他先被大于他的特殊元素交换，然后又被前此时最大特殊元素交换回去(用树状数组求大于的也是1)。
    然后就是为什么我们尽可以通过第一轮动态的更改就可以知道现在这个元素的交换次数，
    因为经过一轮交换过后，其实接下来的每一轮都是把一个元素尽可能的换到前面的位置，并且因为有最大元素的限制，我们换到i就换不动了。
    因为最大值已经跑到这里了，也就是说需要统计的可能的交换次数都是在它前面的。
    于是我们就可对每个非特殊元素进行基本的树状数组操作，同时需要注意的是需要去重，也就是说对于位置上已经有的不在更新，
    简单验证就可知道了。
    
    然后就是最难理解的地方，当某个元素与此时的A[1]相同时，我们就要开始记录，从现在到出现比此时的A[1]大的元素之间有多少个元素，
    因为我们在跑的A[i]的时候我么只是知道现在的最大值是A[1]，于是我们就只统计了前面的大于他的元素的个数，相同的元素只会起到一次的
    作用，如果后面有更大的现在大于他的元素就会增多，所以我们需要记录这个区间有多少元素。
    
 AC代码
 ===
 ```C++
 #include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int maxn = 1e5+10;

int a[maxn],n;
bool vis[maxn];
int tr[maxn];

int lowbit(int x) {return x&-x;}
void add(int x){

	while(x<=n){
		tr[x]+=1;
		x+=lowbit(x);
	}
}
int query(int x){

	int res=0;
	while(x>0){
		res+=tr[x];
		x-=lowbit(x);
	}return res;
}
void solve(){

	scanf("%d",&n);
	for(int i = 1; i <= n ; i++){
		scanf("%d",&a[i]);tr[i]=0;vis[i]=false;
	}
	add(a[1]);vis[a[1]]=true;
	ll ans=0;
	printf("0");
	bool f=false;int cnt=0;
	for(int i = 2 ; i <= n ; i++){
		if(!vis[a[i]]){
			vis[a[i]]=true;add(a[i]);
		}
		if(a[i] == a[1]) f=true;
		cnt+= f?(a[i] <= a[1]) : 0;
		if(a[i] > a[1]) {
			swap(a[1],a[i]);
			ans+=cnt+1;cnt=0;f=false;
		}
		// cout <<i << "  " <<ans << " ";
		ans+=1ll*(query(a[1])-query(a[i]));
		printf(" %lld",ans);
	}printf("\n");
	
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
	int t;scanf("%d",&t);
	while(t--){
		solve();
	}
}
 ```
 ```diff
 !  🥄2021-01-15
 ```
