##  👟[F - Reordering ](https://atcoder.jp/contests/abc234/tasks/abc234_f?lang=en)

    这道题翻译过来其实就是对于每一种字符都有若干种，然后你每次可以选择若干个构成字符串，现在想知道一共有多少
    种排列组合。
    
    那么对于混合来讲一定是难以下手的，我们需要找出一些规律。
    
    我们规定dp[i][j]为使用前i种字符构成长度为j的字符串的种数。
    
    状态转移方程为：  dp[i][j] = dp[i - 1][j - k] * C(k,n)
    
    也就是说，用j - k 个之前字符和 k 当前的字符构成长度为j的字符串，那么这个排列组合就是从j个位置里面选择k个给当前字符，
    剩下的字符按照原来的相对顺序填入剩下的j - k个空中。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 5e3 + 10;
const int mod = 998244353;

i64 dp[30][maxn],f[maxn],inv[maxn];
int cnt[maxn];

i64 ksm(i64 a,int b){

    i64 res = 1;
    while(b){
        if(b&1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1; 
    }
    return res;
}
void init(){

    f[0] = 1;
    for(int i = 1; i < maxn ; i++) f[i] = f[i-1] * i % mod;
    inv[maxn - 1] = ksm(f[maxn - 1], mod - 2);
    for(int i = maxn - 2; i >= 0 ; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}
i64 C(int n,int m){

    if(m == 0) return 1;
    else if(n == 0) return n;

    return f[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    init();
    string s;
    cin >> s;
    for(auto x : s) cnt[x - 'a' + 1]++;

    int len = s.size();
    dp[0][0] = 1;
    for(int i = 1 ; i <= 26 ; i++){

        for(int j = 0; j <= len ; j++){
            for(int k = 0; k <= min(j , cnt[i]) ; k++){
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k] * C(j , k)) % mod;
            }
        }
    }
    
    i64 ans = 0;
    for(int i = 1; i <= len ; i++) ans = (ans + dp[26][i]) % mod;

    cout << ans << endl;

    return 0;
    
}
```

```diff
!     🚛2022-03-04
```
