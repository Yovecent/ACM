#   🌼[D. Journey to Un'Goro](https://codeforces.com/gym/103202/problem/D)

    因为我们想要使得连续的一段中出现奇数个r，所以可以考虑前缀和的l,r小技巧，真的是前缀和常用
    技巧，但是就是想不到呀.......
    
    那么我们只需要选出奇偶性不同的两个两个端点，那么这个区间内就一定会出现奇数个r。
    所以贪心的想，有一半个奇数，一半个偶数的时候一定就是最优的，
    个数就是 ((n + 1) / 2) * ((n + 2) / 2)即为一个上取整，一个下取整，同时又因为多了一个0点，所以n变为n + 1。
    
    
    那么我们只需要使用DFS，因为要字典序最小，所以只需保证次数最多的那个不超过(n + 2) / 2，我们就用b，否则就用r。
    
    同时这里也是用到了回溯的含义，我们不用开那么多个string，只需要定义一下现在走到哪里了，然后回溯回来的时候再更新
    即可。
    
AC代码：
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
int n, tot;
char s[100010];

void dfs(int k, int odd,int even,int pi){

    if(tot >= 100 || max(odd,even) > (n + 2) / 2) return;
    if(k == n){
        s[k] = '\0';
        if(abs(even - odd) <= 1){
            cout << s << endl;
            tot++;
        }
        return;
    }

    s[k] = 'b';
    if(pi & 1) dfs(k + 1, odd + 1,even, pi);
    else       dfs(k + 1, odd, even + 1, pi);
    s[k] = 'r';
    if(pi & 1) dfs(k + 1, odd, even + 1, (pi + 1) % 2);
    else       dfs(k + 1, odd + 1, even, (pi + 1) % 2);

}   
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    cin >> n;
    cout << ((n + 1) / 2) * ((n + 2) / 2) << endl;
    dfs(0, 0, 1, 0);

    return 0;
}
```
```diff
!   2022-03-23💐
```
