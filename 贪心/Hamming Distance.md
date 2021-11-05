# [2018CCPC桂林站:Hamming Distance](https://codeforces.com/gym/102823/problem/H)  

    🥫为什么会有这么妙的题目啊！！！ORZ
    
    真的贪心贪到家了！！！！
    
    首先题目的要求是，我们构造一个与原字符串长度相同的字符串，并且这个字符串在两个原字符串中位置相等且相同的个数相同，
    并且我们要保证他的字典序更小。听起来也不像一道难题，但他就是那么难。
    
    首先对于字典序更小，我们肯定是让前面的用尽可能小的字符。当时只局限于a了，就想着怎么能多用a，但有时候可能用a，这道题
    并不能做出来。
    
    所以我们可以对于每一位都用一个循环，从a到z，不断的去判断如果当前这个字符就以，那我们就用它，接着去考虑下一位。
    
    但怎么判断是不是可以呢？
    
    
    我们考虑一下，设与a相同的个数有cnt1个，与b相同的有cnt2个
    如果a和b在这一位字符是相同的，那么我们不管用什么字符，对字符的构造都是没有影响的。因为他们要不同时增加，要不同时减小
```diff
+    如果不同的我们，我们总能找到方案使得其中的一个增加，而使cnt1和cnt2接近，
    
+    就比如说  a为d    b为e 如果我们想让cnt1增加，就让这一位设为d，让cnt2增加就设为e，又如果我们都不像增加那么设为a就可以了。
```
    那也就是说对于当前字符的修改，我们只用考虑后面还有几个字符不同的位置就可以了,如果cnt1与cnt2不同，我们总能通过那些字符不同的地方
    修改而是cnt1与cnt2的值相同，所以我们更改完这一位的字符之后，只用判断abs(cnt1-cnt2)是否小于后面字符不同的个数即可
    
AC代码如下：
```C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 1e6+10;

char a[maxn],b[maxn];
char ans[maxn];
int sum[maxn];
void solve(){

    int n=strlen(a+1);sum[n+1]=0;
    for(int i = n ; i >= 1; i--){
        sum[i]=sum[i+1];
        if(a[i]!=b[i]) sum[i]++;
    }
    int cnt=0;
    for(int i = 1; a[i] ; i++){
        for(int j = 'a' ; j <= 'z' ; j++){
            if(a[i] == j) cnt++;
            if(b[i] == j) cnt--;
            if(abs(cnt) <= sum[i+1]){
                ans[i]=j;break;
            }
            if(a[i] == j) cnt--;
            if(b[i] == j) cnt++;
        }
    }ans[n+1]='\0';
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int t;scanf("%d",&t);int cases=1;
    while(t--){
        scanf("%s %s",a+1,b+1);
        solve();
        printf("Case %d: %s\n",cases++,ans+1);
    }
    return 0;
}
```
    
