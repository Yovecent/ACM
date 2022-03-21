#  🚑[C. Basic Diplomacy](https://codeforces.com/contest/1482/problem/C)

    思维题杀我呀！！！！
    
    
    这道题确实好，想了很久也没想出来。。。。。
    
    
    其实我们可以想一下，对于每一个天如果我们随便选一个人的，最多只会有一个人超过最大次数。
    那么如果说存在一个合法的方案，我们只需要不断地把每一个是当前这个数的那一天换一个人，就一定会出现正确结果。
    
    那最坏的情况就是我们都把那些不合法的天都换成了另外同一个人，
    但是边界就是我恰好使的那个人变为合法的了，那么这个这个人也一定最多是刚好合法的。也就是说
    最多n / 2次，那么也必定是合法的。
    
    
    真的使太妙了！！！！
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

vector<int>info[200010];
int cnt[200010],ans[200010];

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

        int n, m;
        cin >> n >> m;
        for(int i = 1 ; i <= max(m, n) + 10 ; i++) info[i].clear(), cnt[i] = 0;

        for(int i = 1; i <= m ; i++){
            int k; cin >> k;
            while(k--){
                int x;  cin >> x;
                info[i].push_back(x);
            }
        }

        bool ok = true;
        int op = -1;
        for(int i = 1; i <= m ; i++){
            if(info[i].size()){
                if(++cnt[info[i][0]] > (m + 1) / 2){
                    op = info[i][0];
                }
                ans[i] = info[i][0];
            } else {
                ok = false;
            }
        }
 
        if(!ok){
            cout << "NO" << endl;
            continue;
        } else if (op == -1) {
            cout << "YES" << endl;
            for(int i = 1; i <= m ; i++) cout << ans[i] << " ";
            cout << endl;
            continue;
        }
        ok = false;
        for(int i = 1;  i <= m  && !ok ; i++){
            if(ans[i] != op) continue;
            for(auto x : info[i]){
                if(x != op && ans){
                    ans[i] = x;
                    if(--cnt[op] <= (m + 1) / 2){
                        ok = true;
                    }
                    break;
                }
            }
        }

        if(ok){
            cout << "YES" << endl;
            for(int i = 1; i <= m ; i++) cout << ans[i] << " ";
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
```
```diff
!    2022-03-21🐮
```
