#  🐡[小y的序列](https://ac.nowcoder.com/acm/contest/30880/F)

   
   对于求解区间个数问题我发现一般就两种求的方法:   
   (1)  枚举中心点，然后向两边扩展。  
   (2)  枚举左端点，然后求右端点的个数。
   
   
   写这道题的时候管想着第一种方法了，一直不知道怎么求，这里用的是第二种办法。
   
   首先我们对于求解的条件进行变换：
   Max = Min + k
   Max - Min = k
   也就是说我们需要求解区间 最大值 - 最小值 == k 的区间。 
   而我们想一个问题：
   如果我们定了一个左端点，我们想求出右端点的值，再我们不断往右扩大的同时 Max - Min具有单调不减的性质   
   
   那么我们就可以求出最大的 Max - Min < k的端点， 以及 Max - Min == k的端点
   那么可以选择的右端点就是这两个端点之间的点。
   根据具有单调增的性质，我们可以利用倍增求解右端点。
   
   但是利用倍增的时候我们对于起始点的设定至关重要，需要先考虑走不动以及走的动的情况下有没有区别  
   
   这里一直不知道哪里出错了，对于如果第一个数是合法的话，因为走不动停在第一个，因为走只能走在当前，所以
   这两种情况冲突了，所以需要特判一下。
   
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;

struct ST{

    int st_Max[1000010][30],st_Min[1000010][30];
    void build(vector<int> &a,int n){

        for(int i = 1; i <= n ; i++) st_Min[i][0] = st_Max[i][0] = a[i];

        for(int j = 1 ; (1 << j) <= n ; j++){
            for(int i = 1; i + (1 << j) - 1 <= n ; i++){
                st_Max[i][j] = max(st_Max[i][j - 1], st_Max[i + (1 << (j - 1))][j - 1]); 
                st_Min[i][j] = min(st_Min[i][j - 1], st_Min[i + (1 << (j - 1))][j - 1]); 
            }
        }
    }

    int get(int l,int r){
        int cul = 32 - __builtin_clz(r - l + 1) - 1;
        return max(st_Max[l][cul],st_Max[r - (1 << cul) + 1][cul]) - min(st_Min[l][cul],st_Min[r - (1 << cul) + 1][cul]);
    }
}st;
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int n, k;  cin >> n >> k;
    vector<int>a(n + 1);
    for(int i = 1; i <= n ; i++) cin >> a[i];

    st.build(a, n);
    i64 ans = 0;
    for(int i = 1; i <= n ; i++){
        int r1 = i, len = 1, r2 = i;
        while(len){
            if(len + r1 <= n && st.get(i, r1 + len) < k){
                r1 += len;  len <<= 1;
            } else {
                len >>= 1;
            }
        }
        len = 1;
        while(len){
            if(len + r2 <= n && st.get(i, r2 + len) <= k){
                r2 += len;  len <<= 1;
            } else {
                len >>= 1;
            }
        }
        ans += 1ll * (r2 - r1);
        if(st.get(i,i) == k) ans++;
    }
    
    cout << ans <<endl;
    
    return 0;
}
```
```diff
!  2022-03-26🏸
```
