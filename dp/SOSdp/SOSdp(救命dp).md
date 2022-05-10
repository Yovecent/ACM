<span id="jump0"> </span>

###   title:

  #        [1. Blocks](#jump1)


# [😲SOSdp](https://codeforces.com/blog/entry/45223)

## 1.SOSdp的基本定义

    其全称是Sum over Subsets dynamic programming,简单来说就是对于子集的dp。
    
    假设一共有不超过1 << n个元素的数组A。
    我们的任务是求出F:
    
    F[mask] = ∑ A[i]
              i∈mask    {i & mask == i}
     
    这个可以理解为一种状态压缩，但是这的状态指的是一种罪域一种状态的所有子集的集合。
    
    
> 举例来说：1010     

```diff
    状态压缩：2，5
    SOS    : 0,10,1000,1010
    
!   及之前的状态压缩指的是对于某一位取或不取，但是SOS指的是对于上一个状态压缩的所有子集的集合。
    
```

##  2.SOSdp对于F的获取
    
####  (1)暴力求法O(4^n)：
  
```C++
  for(int mask = 0 ; mask < (1 << n); mask++){
      for(int i = 0 ; i < (1 << n) ; i++){
          if((mask & i) == i)
              F[mask] += A[i]
          }
      }
   }
```

#### (2)迭代一个mask的所有子集O(3^n):

```C++
    for(int mask = 0 ; mask < (1 << n) ; mask ++){
          for(int  i = mask ; i > 0 ; i = (i - 1) & mask){
                F[mask] += A[i]
          }
     }
```
```diff
    对于这种方法其实就是求出对于一个mask的所有子集的表示形式。
    那么对于一个一共有k位上为1的数，那他将会有2^k个子集，即只使用这k个一的组合。
    那么时间为 k:0 -> n  C(n,k)*2^k
    求和之后是3^n
```
#### (3)SOSdp解法 O(nlogn)
```diff
    首先我们来定义一下dp[mask][i]表示对于mask的前i位会不同，而后n - i位与mask一定相同的子集的求和。
    注意：下标从0开始
    
    例如mask = 10110
    dp[mask][1] = {10110,10100}
    dp[mask][2] = {10110,10100,10010,10000}
    那么我们就可以使用dp的思想。
    我们将i 从0到n-1更新。
    假如说来到了第i位：
    如果第i位是0,那么dp[mask][i] = dp[mask][i - 1],因为我们控制后n - i位相同与后n - i + 1相同达到的效果是一样的。
    如果第i位是1,那么dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << i)][i - 1]。
    即我们可以把它分为两类：
    第i位上是1，剩下的i - 1位不同，与第i位上是0剩下的i - 1位不同。
    
```
![image](https://user-images.githubusercontent.com/92497177/156930299-5b45ba1f-6819-459d-8554-380584d08a20.png)
![image](https://user-images.githubusercontent.com/92497177/156930310-4973bc9f-094d-4603-bf28-eb4c06024c49.png)

```C++
//iterative version迭代版本
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][-1] = A[mask];	//handle base case separately (leaf states) 即叶子节点所代表的A[mask]的值
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i))
			dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
		else
			dp[mask][i] = dp[mask][i-1];
	}
	F[mask] = dp[mask][N-1];
}

//memory optimized, super easy to code.记忆化的版本，同时更容易书写
for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
	if(mask & (1<<i))
		F[mask] += F[mask^(1<<i)];
}

```
```diff
    同时需要注意的是，我们如果想用第一种形式的话，要考虑到是否会超内存，因为他是(1<<n)*n的存储。
    
    所以我们一般都会使用第2中书写格式。
    同时为什么第二种形式是正确的呢？
    
    我们考虑，如果a可以更新了b，那说明a与b只会有一位的差距，那么
    
    对于1011：
    那么他的更新一定会是.
    0000 -> 0001
    1000 -> 1001
    1001 -> 1011
    1010 -> 1011
    0001 -> 0011
    0011 -> 1011
    所以一个数只会被他的所有子集所更新。
    
    
    对于记忆化的写法，其实思想和上面的是一样的。
    都是保证前面的几位可能改变，后面的和原串相同的子集的加和。
    因为我们枚举的是数从0 -> n
    其实就对应了二进制的前n位，
    if(mask & (1<<i))  就对应了我们当前如果这一位为1的话，那么我们可以将其加和此位为1，与此位为0的
    集合，因为这两个集合都是他的子集。
    
    同时我们也保证了现在遍历到的都是前i为可能不同，后n - i位一定相同的集合的求和。
```

```diff
!     🛺2022-03-06
```
<br>
<br>
<br>
<br>
 
 [返回](#jump0)
 
 <span id="jump1"></span>
 
  #  🛺[Blocks](https://ac.nowcoder.com/acm/contest/32708/B)
  
![image](https://user-images.githubusercontent.com/92497177/167522568-17d67457-14cc-40d1-9316-d21ac29a1be5.png)

   这道题考查的太多了QAQ ：  SOSdp + 容斥原理 + 状压
   
   首先状压其实是比较好想的，因为数据范围只有10，那么我们状压依旧是是所用元素的集合。
   
   其次就是我们怎么算出我们已经选择的矩形构成的图形的整体的面积呢？
   
   傻了吧唧的，把容斥原理给忘了吧，黄老师当时画的图依旧记得，只是人已经傻到完全忘记了。
![image](https://user-images.githubusercontent.com/92497177/167523278-df47b158-f70b-407a-91b3-524af28b1f11.png)
  
   这里我们用的依旧是奇加偶减。
   那么我们需要算出每一个集合的交，然后按照奇加偶减的规则算出总的面积。
   那么我们这里其实就已经引出了子集的概念。
   
   但是怎么算很多矩形的交呢？
   我们可以维护四个边界。
   xl, yl, xr, yr
   即为左，下，右，上
   我们让左边界取到最大的左边界，有边界取到最大的有边界，同理对于上和下。
   那么这个就是我们的交集。
   
```C++
		vector<i64>s(1 << n, 0);
		for(int j = 0 ; j < (1 << n) ; j++){
			int xl = 0, xr = W, yl = 0, yr = H; //这里的xl,xr,yl,yr的设置很重要,即为我们要统计的矩形的边界
			
			for(int i = 0 ; i < n ; i++){
				if(j & (1 << i)){
					xl = max(xl, X1[i]);
					xr = min(xr, X2[i]);
					yl = max(yl, Y1[i]);
					yr = min(yr, Y2[i]);
				}
			} 
			s[j] = 1ll * max(0, (xr - xl)) * max(0, (yr - yl));
		}
```

    然后算完了子集，之后就是子集的合并了。
    依旧拾起我们遗忘的算法:SOSdp,
    SOSdp可是为了子集而生的一个算法。
    上面又对SOSdp记忆化的形式进行了补充，如果又忘了就再往上翻吧。
    
    同时我们需要对集合进行初始化。
    这里的初始化我们需要对其进行奇偶性的判断，这里我们只需要对其按照二进制中的1的个数的判断即可。
    因为其二进制中的一的个数就对应了我们选择的矩形的个数。
    
```C++
	for(int i = 1 ; i < (1 << n) ; i++) S[i] = (__builtin_parity(i) ? 1 : -1) * s[i];
	for(int i = 0 ; i < n ; i++){
		for(int j = 0; j < (1 << n) ; j++){
			if(j & (1 << i)){
				S[j] += S[j ^ (1 << i)];
			}
		}
	}
```
    
    接下来就是我们对于答案的统计了。
    
    我们设定dp[mask]表示选出mask这个集合时还需要多少步才能结束。
    所以我们的目标就是求出dp[0]
    
    对于一个dp[mask]的计算分为两种情况：
    
    1.如果对于S[mask]即为其所覆盖的面积已经包含了 完整的矩形那么 dp[mask] = 0，即现在我们已经不需要选择了。
    
    2.如果此时还得选，
    我们先统计一下已经选过了的元素的个数 cnt(即看里面有多少个1)
    
    又因为现在是等概率的选择，所以我们又有两种情况：
        (1) 选到了一个现在已经选过的元素
	(2) 选到了一个现在还未选过的元素，此时我们就会将其转化为另一种mask (mask ^ (1 << i))
     
    那么dp[mask] = 1 + cnt / n * dp[mask] + ∑(所有转化成的另一种集合的答案的求和) / n
    
    1 ： 对应我们这一次做出了一个选择   
    cnt / n * dp[mask] ： 对应我们选择已存在的那么我们还是转化成了原来的集合
    ∑(所有转化成的另一种集合的答案的求和) / n：  对应我们等概率的选择未选择过的数转化之后答案的期望 即为 1 / n * dp[x]的求和
    
    那么我们整理一下
    dp[mask] = (n + ∑) / (n - cnt)
    所以我们只需要求出来之前的状态，那么倒叙就可以了。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int mod = 998244353, INF = 0x3f3f3f3f;

int inv[11];
i64 ksm(i64 a, int b){
	
	i64 res = 1;
	while(b){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
void get_birany(int x){
	
	vector<char>s;
	while(x){
		s.push_back(x % 2 + '0');
		x /= 2;
	}
	reverse(s.begin(), s.end());
	for(auto x : s)  cout << x;
}
int main()
{
	inv[0] = 1;
	for(int i = 1; i <= 10 ; i++) inv[i] = ksm(i, mod - 2);
	
	int t;  scanf("%d",&t);
	while(t--){
		int n;  scanf("%d",&n);
		
		int H, W;  scanf("%d %d",&W, &H);
		i64 SS = 1ll * W * H;
		vector<int>X1(n), Y1(n), X2(n), Y2(n);
		for(int i = 0; i < n ; i++){
			scanf("%d %d %d %d",&X1[i], &Y1[i], &X2[i], &Y2[i]);
		}
		
		vector<i64>s(1 << n, 0), S(1 << n, 0), dp(1 << n, 0);
		for(int j = 0 ; j < (1 << n) ; j++){
			int xl = 0, xr = W, yl = 0, yr = H;
			
			for(int i = 0 ; i < n ; i++){
				if(j & (1 << i)){
					xl = max(xl, X1[i]);
					xr = min(xr, X2[i]);
					yl = max(yl, Y1[i]);
					yr = min(yr, Y2[i]);
				}
			} 
			s[j] = 1ll * max(0, (xr - xl)) * max(0, (yr - yl));
		} 
		
		for(int i = 1 ; i < (1 << n) ; i++) S[i] = (__builtin_parity(i) ? 1 : -1) * s[i];
		for(int i = 0 ; i < n ; i++){
			for(int j = 0; j < (1 << n) ; j++){
				if(j & (1 << i)){
					S[j] += S[j ^ (1 << i)];

				}
			}
		}
		if(S[(1 << n) - 1] != SS){
			printf("-1\n");continue;
		}
		
		for(int j = (1 << n) - 1 ;  j >= 0 ; j--){
			if(S[j] == SS)  continue;
			
			int cnt = 0;
			i64 sum = 0;
			for(int i = 0 ; i < n ; i++){
				if(!(j & (1 << i))){
					sum += dp[j ^ (1 << i)];
					sum %= mod;
				} else cnt++;
			}
			
			dp[j] = (n + sum) % mod * inv[n - cnt] % mod;
		}
		
		printf("%lld\n", dp[0]);
	}
	
	return 0;
}
```

```diff
!   2022-05-10🧺
```
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
