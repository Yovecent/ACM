#   🩹[King of Gamers](https://ac.nowcoder.com/acm/contest/32708/K)

  真的是没有这方面的思想，完全没有找到规律。。。。。。
  
  
  首先这道题暴力打表，我们来观察一下：
  
  ![image](https://user-images.githubusercontent.com/92497177/163835802-2231e503-f4d2-41b7-be88-1aff46b0c5fb.png)

 在某些位置需要我们去加1，但是这是什么时候呢？
 
  因为要加1，其实我们应该有这方面的一些想法，比如说进位。
  
  什么时候要进位？
  四舍五入， 向上取整， 或是针对于整数的向上取整？
  
  其实我们都可以去验证的，真的是没有一点经验，明明可以去一点一点的验证，因为猜结论无非就这些。
  
  
  而这次考的就是一个比较难想的整数的向上取整。
  
  将n - 1,然后直接输出 n * a / b + 1
  
  
  这里其实队友最后做出来的方法和这个就差不多了，我们都是要比一下n - 1 和 n 的效果。
  将n - 1的答案算一下，然后比一下此时的胜率再算用不用进位。
  
```C++
#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using i64 = long long;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	
	int t;  cin >> t;
	while(t--){
		
		i64 n, a, b;  cin >> n >> a >> b;
		n--;
		cout << n * a / b + 1 << endl;
	}
	return 0;
}
```
```diff
!   2022-04-19🏖️
```
