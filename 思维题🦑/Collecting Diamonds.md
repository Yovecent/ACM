  # [Collecting Diamonds](https://codeforces.com/gym/103743/problem/L)
![image](https://user-images.githubusercontent.com/92497177/170850950-c79c7919-936b-404a-8045-7af6c6d4b56d.png)
    
    首先我们知道对于一个AAABCCC类型的串，我们可以将其分离出来，其实相当于一个单独的整体。
    因为我们想要拿AC的话，就只能从中间不断地向两边扩散，同时我们如果将其中的B拿走之后，那么剩下的AACCC集合也再不会
    对答案有贡献。
    
    那么我们将他们记为下面的形式:
    <奇,num>  <偶,num>即代表现在的每一个整体的奇偶操作情况(奇偶为最后一个A的下标的奇偶性，num为min(A,C))
    例如样例一我们将其改为<奇,1><偶,3>
    
    如果我们执行了一个奇操作，它会变成偶操作，后面的每一个整体的奇偶性是没有影响的(因为我们拿了两个)。
    同时如果我们执行了一个偶操作，它会变成一个奇操作，同时后面的每一个整体奇偶性发生变化，并且当前这个集合不会再对答案有贡献(B被拿走了)
    
    
    那么我们贪心的去想，我们肯定是要尽可能多的进行奇操作(拿走AC)，因为偶操作只能做一次。同时我们如果想要让当前这个集合能够做
    很多次的奇操作的话，那么我们就需要让其前面的集合做一定数量的偶操作，因为我们此时已经变为偶操作则需要前面的执行偶操作将我们
    的偶操作变为奇操作。
    
    因为我们当前的这个整体能够做多少的奇操作取决于前面的总的偶操作的次数，所以我们就让每一个集合的最后一次操作为偶操作，看一下其
    最多能进行多少的奇操作，这里进行当其为奇偶时统计有一些不一样。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = 2e5 + 10;

char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    scanf("%s", s + 1);
    int n = strlen(s + 1);
    vector<pair<int,int> >v;
    for(int i = 1; i <= n ; i++){
        if(s[i] != 'B') continue;
        int len = 0;
        while(i - len - 1 >= 1 && i + len + 1 <= n && s[i - len - 1] == 'A' && s[i + len + 1] == 'C') len++;
        if(len) v.push_back({(i - 1) & 1, len});
    }

    int ans = 0, lazy = 0;
    for(int i = 0 ; i < v.size() ; i++){
        if(v[i].first & 1){
            if(!lazy && v[i].second == 1){
                ans++;
            } else {
                ans += min(v[i].second - 1, lazy + 1) + 1;
                lazy++;
            }
        } else {
            ans += min(v[i].second - 1, lazy) + 1;
            lazy++;
        }
    }

    printf("%d\n",ans);

    return 0;
}
```

```diff
!   🏹2022-05-29
```
