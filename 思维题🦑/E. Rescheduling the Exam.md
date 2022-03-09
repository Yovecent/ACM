# 🐡[E. Rescheduling the Exam](https://codeforces.com/contest/1650/problem/E)
    
    当时先开始想得二分，然后觉得二分没有必要，就是直接贪心就行，但是越想越乱。
    
    首先因为我们只能移动一个考试时间，所以我们需要先找出相距最短的那一段，
    我们就只要移动这个区间左右两个考试中的其中一个就可以求出最大值了。
    
    我们并不用讨论这个最小值是否唯一，即是否有多个最小值，因为如果有超过两个最小值，或是有两个最小值
    但是他们没有一个公共的端点的话，其实最小值是不改变的。因为我们只可以移动一个，那就最多会影响两个值。
    
    所以我们只需要进行两次判断就可以了。
    即将其中的一个删掉，然后找出现在区间的最小值，与最大值。
    那我们的方案就有两种，第一种放在最大值的中间，第二种放在最后一天。
    
```C++
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
using i64 = long long;
const int INF = 0x3f3f3f3f;

int n,d;

int ok(vector<int> &info){

    int Min = INF,Max = 0;
    for(int i = 1; i < info.size() ; i++){
        Min = min(Min, info[i] - info[i - 1] - 1);
        Max = max(Max, info[i] - info[i - 1] - 1);
    }

    return min(Min,max((Max - 1)/2, d - info.back() - 1));
}
void solve(){

    int Min = INF,pos;
    cin >> n >> d;
    vector<int>a(n + 1),info(1);
    for(int i = 1 ; i <= n ;i++){
        cin >> a[i];
        if(a[i] - a[i-1] - 1 < Min){
            Min = a[i] - a[i-1] - 1;
            pos = i;
        } 
    }
    for(int i = 1; i <= n ; i++){
        if(i != pos){
            info.push_back(a[i]);
        }
    }

    int ans = ok(info);

    if(pos != 1){
        info[pos - 1] = a[pos];
        ans = max(ans,ok(info));
    }
    cout << ans << endl;
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
```

```diff
!     🚛2022-03-10
```
