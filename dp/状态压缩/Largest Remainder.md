  <br>  
  
  +    <strong>[Largest Remainder](#jump1)  
  +    <strong>[P4163 [SCOI2007]排列](#jump2)  
  
  <br>
  
<span id="jump1"></span>   

#  ⚓[Largest Remainder](https://codeforces.com/gym/103443/problem/D)
    
    这道题很容易看出来是状压，但是并不知道怎么转化。
    zyz秒懂写法，最后极限998ms强势通过。
    
    这道题官方题解里面给的时间复杂度是O(2^D * D * K)，其实这样算下来最坏时间复杂度
    为2e8,但是这是cf神机。
    其实zyz的方法很好，但是被卡时间的地方就在于开的dp表示的是数，所以是long long类型的，那
    就会比int的慢一倍。
    
###   方法一：直接表示最大值
```diff
!     dp[S][r] 表示使用集合为S的数字，表示出余数是r的最大的数。

      那么我们最后输出的答案就是dp[(1 << D) - 1][r]
```
    
    那么我们的初始化就是将所有的dp[S][r] 标记为-1表示未到达
    并将dp[0][0] = 0即为入口
```C++
    for(int i = 0 ; i < (1 << D) ; i++){
        for(int j = 0 ; j < k ;  j++){
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;
```

    那么我们每次从一个可达的地方向未到达的地方转移：
    即我们需要查询出dp[S][r]中缺哪一位，然后将异或S得到转移后的集合，然后更新最大值。
    
```C++
    for(int mask = 0 ; mask < (1 << D) ; mask++){
        vector<int>a;
        for(int i = 0 ; i < D ; i++) if(!(mask & (1 << i))) a.push_back(i);//找出还未在这个集合中出现的数
        for(int i = 0 ; i < k ; i++){
            if(dp[mask][i] == -1) continue;
           for(int p = 0 ; p < (int)a.size() ; p++){

                int op = (dp[mask][i] * 10 + num[a[p]]) % k; //新的余数
                dp[mask | (1 << a[p])][op] = max(dp[mask | (1 << a[p])][op], now); //将其变为可达
           }
        }
    }
```
    那我们最后从大的余数向小的余数遍历，如果有值就直接输出
    总的来说思想挺好的，但是就是因为开的是long long所以时间和空间上就会不太优秀，但是zyz人品太好了，cf直接跪下。
ACcode:
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

i64 dp[100000][201];

int main()
{

    int D, k;  scanf("%d %d",&D,&k);
    vector<int>num(D);
    for(int i = 0 ; i < D ; i++)  scanf("%d",&num[i]);

    for(int i = 0 ; i < (1 << D) ; i++){
        for(int j = 0 ; j < k ;  j++){
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;
    for(int mask = 0 ; mask < (1 << D) ; mask++){
        vector<int>a;
        for(int i = 0 ; i < D ; i++) if(!(mask & (1 << i))) a.push_back(i);
        for(int i = 0 ; i < k ; i++){
            if(dp[mask][i] == -1) continue;
           for(int p = 0 ; p < (int)a.size() ; p++){

                i64 now = (dp[mask][i] * 10 + num[a[p]]);
                int op = now % k;
                dp[mask | (1 << a[p])][op] = max(dp[mask | (1 << a[p])][op], now);
           }
        }
    }   
    for(int i = k - 1 ; i >= 0 ; i--){
        if(dp[(1 << D) - 1][i] != -1){
            printf("%lld\n",dp[(1 << D) - 1][i]);
            return 0;
        }
    }
    return 0;
}
```
### 方法二：反向回路输出答案

```diff
!    dp[S][r]:表示用集合为S的数是否可以表示出余数为r的数字。
     我们知道，我们其实是从一个集合向另一个集合去更新，那么我们如果知道可以用S表示出来一个余数为r的数字，那么我们除去一个数字
     ，剩下的S的集合对应的减去之后的余数的dp值也一定成立。
     那么我们只需要从高位到低位去贪心的输出最大值，如果可以的那就一定有一条通路可以回到dp[0][0]

```

   对于状压的更新其实和zyz的写法差不多，但是又有一些不同，因为之前dp存的是数，所以我们可以很好求得变化之后的
   余数：(dp * 10 + num) % k
   同时这里我也思考一下，因为其实我们有两种选择，加到集合的末尾还是加到集合前面，我们只需要考虑其中一种就可以了，
   就比如说 101110
   可以由 001110, 100110, 101000, 101100 转化过来，那这样的话其实就是排列了，所以我们只需要一直考虑一种就可以了。
   
   这里我们考虑加到最高位那么我们就是让选中的数字num乘上十进制下的权重 (num * p[i] + r) % k  
              加到最低位我们考虑取模公式  
              假设原来的数为x：  ((x * 10) % r + num) % r   
                                ( (x % r) * (10 % r) + num % r) % r
                                又因为x % r就是我们算好的模数，所以转移的值就是
                                (r * (10 % k) + num) % k 
                                
                                
    最后就是贪心的走一条回到dp[0][0]的路，真的是太妙了！！！！
    
ACcode, times:436ms
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

bool dp[100000][201];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int D, k;
    scanf("%d %d",&D, &k);
    vector<int>num(D);  vector<i64>p(D + 1);
    p[1] = 1 % k;
    for(int i = 2 ; i <= D ; i++) p[i] = p[i - 1] * 10 % k;

    for(int i = 0 ; i < D ; i++) scanf("%d",&num[i]);
    sort(num.begin(), num.end());

    dp[0][0] = true;
    for(int mask = 1 ; mask < (1 << D) ; mask++){

        int high = __builtin_popcount(mask);
        for(int i = 0 ; i < D ; i++){
            if(mask & (1 << i)){
                for(int r = 0 ; r < k ; r++){
                    if(dp[mask ^ (1 << i)][r]){
                        dp[mask][(r * 10 % k + num[i]) % k] = true; //加到末尾
                        //dp[mask][(r + num[i] * (int)p[high] % k) % k] = true; //加到最高位
                    }
                }
            }
        }
    }

    for(int mask = k - 1; mask >= 0 ; mask--){
        if(dp[(1 << D) - 1][mask]){ 

            int S = (1 << D) - 1, r = mask;
            vector<bool>vis(D);
            for(int pos = D ;  pos >= 1 ; pos--){
                for(int i = D - 1; i >= 0 ; i--){
                    if(!vis[i] && dp[S ^ (1 << i)][((r - p[pos] * num[i] % k) % k + k) % k]){

                        printf("%d",num[i]);
                        vis[i] = true;
                        S = S ^ (1 << i);
                        r = ((r - p[pos] * num[i] % k) % k + k) % k;
                        break;
                    }
                }
            }
            return 0;
        }
    }

    return 0;
}
```
   
```diff
!   2022-05-02🚴‍♀️
```
<br>
<br>
<br>
<span id="jump2"></span>
<br>

#  🧃[P4163 [SCOI2007]排列](https://www.luogu.com.cn/problem/P4163)  
  ![image](https://user-images.githubusercontent.com/92497177/166399727-6ed75fb6-d01d-409b-8b22-53ef401fed96.png)

  

   这道题是上面的原型，刚开始还感觉这个比之前的那个难，但是看了答案之后还是icpc的更难一些。
   在这道题里面最重要的就是因为会有重复的数，所以一开始一直不知道怎么统计，但是其实我们还是按照之前的办法。
   只需要最后对答案按照排列组合方式去重就可以了。
   
   因为我们一定会把所有的数全部选下来，所以就一定是考虑到所有排列的所有情况，那么也就是说如果存在重复的数，
   我们交换重复的数一定也是一个正确答案，那么我们只需要将其除以每一种数的A的方案即可。
   
   之前一直在想只有相同的数相邻会使得答案重复，但其实不相邻也会重复。

```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int dp[(1 << 10)][1001];
int f[11];

int main()
{
    f[0] = 1;
    for(int i = 1; i <= 10 ; i++) f[i] = f[i - 1] * i;

    int t;  scanf("%d",&t);
    while(t--){
        memset(dp, 0 , sizeof dp);

        int n, d;
        string s;  cin >> s >> d;  n = (int)s.size();
        vector<int>a(n);
        for(int i = 0 ; i < n ; i++) a[i] = s[i] - '0';

        dp[0][0] = 1;
        for(int i = 0 ; i < (1 << n) ; i++){

            for(int j = 0 ; j < n ; j++){
                if(i & (1 << j)){
                    for(int k = 0 ; k < d ; k++){
                        int r = (k * 10 + a[j]) % d;
                        dp[i][r] += dp[i ^ (1 << j)][k];
                    }
                }
            }
        }

        int ans = dp[(1 << n) - 1][0];
        vector<int>num(10);
        for(int i = 0; i < n ; i++) num[a[i]]++;
        for(int i = 0; i < 10 ; i++) ans /= f[num[i]];

        printf("%d\n", ans);
    }
    
    return 0;
}
```


```diff
!    😲2022-05-03
```
