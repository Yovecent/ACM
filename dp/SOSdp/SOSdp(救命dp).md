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
```

```diff
!     🛺2022-03-06
```
