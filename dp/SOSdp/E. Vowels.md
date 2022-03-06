#  🉑[E. Vowels](https://codeforces.com/contest/383/problem/E)

###  （1）SOSdp求与mask无交集的元素个数
    在这道题中我们需要求出的是与mask有交集的元素的个数。
    
    这里的有交集的意思是，对于mask的所有1的位置，i至少有一个1个与mask的位置相同。
    那这显然并不是SOSdp数组能够求出来的东西。
    
    那么我们思考一下如果我们相求出来与mask有交集的元素的个数，那么我们取一下反
    MASK = ^mask,  那么 F[MASK]即为与mask无交集的元素的个数。
    
    如果我们知道了与mask无交集的元素的个数，那么有交集的元素的个数就是n - F[MASK]
    Binggo!!!答案就知道了。
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = (1 << 24);

int F[maxn + 10];

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 0 ; i < n ; i++){

        string s;
        cin >> s;

        int x = 0;
        for(int j = 0 ; j < 3 ;  j++){
            x |= (1 << (s[j] - 'a'));
        }

        for(int mask = x ; mask > 0; mask = (mask - 1) & x){

            if(__builtin_popcount(mask) & 1){
                F[mask]++;
            } else {
                F[mask]--;
            }
        }
    }

    for(int i = 0 ; i < 24 ; i++){
        for(int mask = 0 ; mask < maxn ; mask++){
            if(mask & (1 << i)){
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }

    i64 ans = 0;
    for(int i = 0 ; i < maxn ; i++){

        ans ^= 1ll * (F[i] * F[i]);
    }
    cout << ans << endl;

    return 0;
}
```

###  (2)鸽巢原理+SOSdp

    没想到吧，这道题还可以用鸽巢原理，早忘了吧！！！
    
    我们想一下，如果只考虑已经选出的元音的字母，又因为我们的单词都是3个，那么所含的元音的可能情况是：0，1，2，3。
    
    那么对于mask,即已经选好的元音类别，那么正确单词 = 含一个元音的单词数 - 含两个元音的单词书 + 含三个元音的单词数
    又因为F[mask]等于对于mask所有子集的求和，所以我们就会把所有满足的情况都相加，那正好满足鸽巢原理的求解方法。
    
    我们只需要标记含1个和3个的为1，含两个为-1，然后高维求前缀和就可以了。
    
    同时对于一个单词，我们要求出他的所有子集，并按照上述条件去更新F[mask]，这样才能保证一个单词更新了所有的与其有交集的集合。
    
    
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int maxn = (1 << 24);

int a[maxn],F[maxn];

int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 1; i <= n ; i++){

        string s;
        cin >> s;
        int x = 0;
        for(int j = 0 ; j < 3 ; j++){
            int to = s[j] - 'a';
            x |= (1 << to);
        }
        F[x]++;
    }
    for(int i = 0 ; i < 24 ; i++){
        for(int mask = 0 ; mask < maxn ; mask++){
            if(mask & (1 << i)){
                F[mask] += F[mask ^ (1 << i)];
            }
        }
    }
    i64 ans = 0;
    for(int i = 0 ; i < maxn ; i++){
        ans ^= 1ll * (n - F[i]) * (n - F[i]);
    }

    cout << ans << endl;
    return 0;
}
```
```diff
!  🐡2022-03-07
```
