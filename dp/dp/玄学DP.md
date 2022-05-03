   
    
 #     1  [I. Seesaw](#jump1)
    
    
<br>
<br>
  <span id="jump1"></span>
  
  #   🍼[I. Seesaw](https://codeforces.com/gym/103443/problem/I)
  ![image](https://user-images.githubusercontent.com/92497177/166492667-47c3f952-8c36-4fba-a793-d3fe9e28d913.png)
![image](https://user-images.githubusercontent.com/92497177/166492885-f51b7cf2-262e-4a79-853e-99cfb27137e7.png)


    首先看到这道题其实很容易想到是背包问题，但是对于状态的转移并不好想，一开始想着对左右两边进行背包，然后枚举背包容积，
    去看是否有相同的交换个数使得两边相同，这其实就是穷举了所有可能性。  
    一开始一直在这楼里卡住 ，一直不想穷举所有情况，而想是否可以只存下使得到达背包容积时最小的交换个数。   
    
    但这样想一下其实很接近正确答案了。  
    我们想一下对于完整的01背包的时间与空间的分析：  
    dp[i][j][k]对于前i个物品，使用其中的k个物品是否可以达到达到容积为j的背包。  
    那么就是n * n * 5050  
    
    这里的5050的意思时我们假设左边每一个都是1，那么每一个都可能被交换，那么总的就是(1 + 100) * 100 / 2
    所以总的时间和空间就是 5e7,但是加上T的话感觉可能会超呀QAQ
    
    
    我们思考一下，如果我们选择了左边的一些和右边的一些进行交换，左边的总的代价和为A,右边的为B,
    那么此时的差值就是     A - 2 * B
    那么我们交换之后就是   A * 2 - B
    做差之后：
            A + B
    也就是说我们选择左边的背包容积为A的和右边的背包容积进行交换之后会导致两边的差增加A + B
    
    那么思路就很明显了：
    我们先提前算一下两边此时的差 sum
    因为两边的选择的个数是相同的，那么我们枚举左边的情况：选择个数以及选择的背包容积
    
    那么如果我们想要使得sum = 0就说明 A + B = -sum
    所以此时的B的值应该为 - sum - A
    那么我们查询一下是否有与当前个数相同以及背包容积为- sum - A的背包
    有的话就是答案了。
    
    
    
ACcode:
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

bool dp1[101][5060],dp2[101][5060];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int t;  scanf("%d",&t);
    while(t--){

        int n;  scanf("%d",&n);
        int sum = 0, sum1 = 0, sum2 = 0;
        vector<int>a,b;
        for(int i = 1; i <= n ; i++){
            int x; scanf("%d",&x);
            if(x == 1) a.push_back(i), sum1 += i;
            sum += x * i;
        }
        for(int i = 1; i <= n ; i++){
            int x; scanf("%d",&x);
            if(x == 2) b.push_back(i), sum2 += i;
            sum -= x * i;
        }
 
        if(sum > 0){
            printf("-1\n"); continue;
        }

        for(int i = 0 ; i <= (int)a.size() ; i++)
            for(int j = 0 ; j <= sum1 ; j++) dp1[i][j] = 0;
        for(int i = 0 ; i <= (int)b.size() ; i++)
            for(int j = 0 ; j <= sum2 ; j++) dp2[i][j] = 0;

        dp1[0][0] = 1;
        for(int i = 0 ; i < (int)a.size() ; i++){
            for(int j = (int)a.size() ; j >= 0 ; j--){
                for(int k = sum1 ; k >= a[i] ; k--){
                    if(dp1[j][k - a[i]]) dp1[j + 1][k] = true;
                } 
            }
        }

        dp2[0][0] = 1;
        for(int i = 0 ; i < (int)b.size() ; i++){
            for(int j = (int)b.size() ; j >= 0 ; j--){
                for(int k = sum2 ; k >= b[i] ; k--){
                    if(dp2[j][k - b[i]]) dp2[j + 1][k] = true;
                } 
            }
        }

        bool ok = false;
        for(int i = 0 ; i <= min((int)a.size(), (int)b.size()) && !ok ; i++){
            for(int j = 0 ; j <= sum1 ; j++){
                
                int B = -sum - j;

                if(dp1[i][j] && B >= 0 && B <= sum2 && dp2[i][B]){
                    printf("%d\n",i);
                    ok = true;
                    break;
                }
            }
        }
        if(!ok){
            printf("-1\n");
        }
    }

    return 0;
}
```

```diff
!   2022-05-04🚡
```
