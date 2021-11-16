# 🚄[P3084 [USACO13OPEN]Photo G](https://www.luogu.com.cn/problem/P3084)
    
    🏹这道题本来是按照差分约束写的，但是这个dp的思想真的是太强了！！！ORZ
    
    
    首先定义 f[i] 表示在i位置有斑点牛的最大的可能数量，如果f[i]==-1，代表无法再次有斑点牛。
    
    那么更新此处的f值为两种情况：
    
 ##  (1)    
![image](https://user-images.githubusercontent.com/92497177/141986793-aea4ce84-9160-4ece-966e-639a88ad09e2.png)  

    那么能更新他的j一定比图中的j都小，因为i已经覆盖了所有的区间，那么j就只能从最左端更左的点去
    更新它，所以我们用minl[i]代表所有覆盖i的最左的端点值-1的值。
##   (2)
![image](https://user-images.githubusercontent.com/92497177/141987330-7d5c6eba-0fc7-44b9-86e0-dae2a43cedcd.png)
    其实对于覆盖了i的也是一样的，这种状态下我们求的是不覆盖i的区间中左端点值最大的，即为maxl[i]的定义
    
    
    我们把minl[i]都初始为i-1,对于minl[i]我们可以利用的的是小于minl的所有数，对于当前点，所以如果右边的点的minl值
    比我们当前的小，那说明我们可以用其更新当前点，因为右边点的区间覆盖到了我们这个点，所以我们只要在反向遍历一圈就
    把所有点的minl值都求出来了。
    
    
    对于maxl,我们取得是大于maxl的点。同样的，我们考虑当前点，如果小于他的点的maxl值比他大，那就需要更新，因为这中间
    出现了新的区间使得最开始的不成立。
    
    所以对于一个点我们可以去更新f[i]的值是maxl[i] <= j <= minl[i],并且maxl和minl都是单调不减的。也就是说如果我们已经
    把能够更新当前值的所有j点，那么对于下一个我们只用把小于maxl并大于队顶的加入，把小于maxl的队尾的元素删去即可，所以
    删除和加入时间复杂度为O(n)。所以可以用单调队列。
    我们先把所有小于minl的j都加进来并且把小于它的都弹出，因为我们先加进去的下边标更小，所以我们从下往上删除下标小于
    maxl的，剩下的就是合法的值，同时我们只用拿最下面的点去更新f[i]就可以了，因为对于这个单调队列满足，从头到尾，下标值
    逐渐减小，f值逐渐增大。
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int maxn  = 2e5+10;

int n,m;
int minl[maxn],maxl[maxn],q[maxn],a[maxn];
int f[maxn];
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= n+1 ; i++){
        minl[i]=i-1;
    }
    for(int i = 1; i <= m ; i++){
        int l,r;scanf("%d %d",&l,&r);
        minl[r]=min(minl[r],l-1);
        maxl[r+1]=max(maxl[r+1],l);
    }
    for(int i = 1; i <= n+1; ++i){
        maxl[i]=max(maxl[i],maxl[i-1]);
    }
    for(int i = n ; i >= 1; i--){
        minl[i]=min(minl[i],minl[i+1]);
    }
    int j=1;int t=1,h=1;q[1]=0;
    for(int i = 1; i <= n+1; i++){
        for(;j<=minl[i];j++){
            if(f[j]!=-1){
                while(t>=h && f[q[t]] < f[j]) t--;
                q[++t]=j;
            }
        }
        while(h<=t && q[h]<maxl[i]) h++;
        if(h>t) f[i]=-1;
        else    f[i]=f[q[h]]+(i!=n+1);
    }
    printf("%d\n",f[n+1]);
    return 0;
}
```
