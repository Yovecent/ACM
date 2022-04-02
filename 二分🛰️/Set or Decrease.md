#  🥛[Set or Decrease](https://www.luogu.com.cn/problem/CF1622C)

+   所以说二分是useful algorithm呀！！！

    首先贪心的去想，我们肯定是让最小的值去执行第一个操作，然后再让大于他的的数执行第二个操作。
    因为对于大于他的数，我们执行第二个操作一定不会坏于第一个操作，因为执行第一个操作至少会
    让他减少一个。
    
    
    所以我们的计算答案  = 操作一 + 操作二
    
    而我们知道，我们需要做的就是让最小值执行操作一，然后从最大值到最小值去执行操作二，尽管我们不知道
    在那种情况下会最小，以及怎么变一下会更优化，但是只要我们定一了一个答案，我们就一定用O(n)的复杂度找出来。
    这样他还是具有单调性的，即步骤越多越有可能做到。
    对于每一次的mid，我们从后往前，假设对这几个执行操作二，那么我们剩下的操作就去给最小值，计算出一个答案比一下
    是否成立了。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

i64 a[200010], k;
int  n; 
bool check(i64 mid){

    i64 sum = 0;
    for(int i = 0 ; i <= min(mid, 1ll * (n - 1)) ; i++){
        i64 cnt = mid - i;
        sum += a[i];
        if(sum + cnt - (a[n] - cnt) * i >= k) return true;
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;  cin >> t;
    while(t--){

        cin >> n >> k;
        i64 sum = 0;
        for(int i =  1 ; i <= n ; i++)  cin >> a[i], sum += a[i];
        sort(a + 1, a + n + 1,[](i64 x,i64 y){
            return x > y;
        });
        k = sum - k;

        i64 l = 0, r = a[n] + n - 1;
        while(l < r){ 

            int mid = l + r - 1 >> 1;
            if(check(mid)){
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        cout << r << endl;
    }
}
```
```diff
!   2022-04-02 🐤
```
