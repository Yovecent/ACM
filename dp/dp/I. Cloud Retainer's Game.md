🚡[I. Cloud Retainer's Game](https://codeforces.com/gym/103470/problem/I)
=======
![image](https://user-images.githubusercontent.com/92497177/149886479-30700656-88d9-4b17-84af-3b673e5f6030.png)  

![image](https://user-images.githubusercontent.com/92497177/149886325-397215de-098f-4930-98af-f10ee2cc1726.png)  
    
    额，这是人说的话吗？我这辈子都想不出来呀。。。。。
    首先我们考虑，小球的行动轨迹一定会沿着y=x+k,y=-x+k进行移动。
    如果没有挡板的话，那么向上时 y=x,y=x+2*H,y=x+3*H..... 向下时 y=-x+2*H,y=-x+4*H..... 及两个会关于y = H 对称，并且k值
    会增大2*H，那么我们变换以下公考虑一般情况。
    y+x = k,2*H+x-y = k然后如果再算上向右移动的所有线段，那么对于(y+x)%2H = k ，以及 (2H+x-y)%2H = k的的点就都是在一条只与
    顶或底碰撞过的三角曲线上移动，那么此时就用到的动态规划的思想，即不断对状态进行更新。
    我们试想一下如果我们求出这个点的k1与k2，那么我们就可以认为这个点是沿着这两条线中的其中一条过来的，
    而如果我们碰到一个金币的话，我们就可以让这两个k1,k2的f值都加上一，即对于状态的基本更新。
    其次如果我们遇到了一个挡板，因为我们既可以反向走也可以将挡板去掉而正向走，所以我们就可以让这两条线的f值都取到他们中的
    最大值，如果他被更新了，那么是因为另一条线撞到挡板转向了。
    
    其次我们还需要注意的是，我们利用的线一定是被更新过的线，这代表我们之前能到这条线，所以这里的处理方式是初始化f[0]为1，
    在遇到金币时，只有f[k]>0的点才会被更新。
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <cstring>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;

int n,m;
unordered_map<int,int>f;
struct node{

    int x,y,k;
    node(){};
    node(int x,int y,int k):x(x),y(y),k(k){};
}p[maxn<<1];
void solve(){
    int h;scanf("%d",&h);int H=2*h;
    f.clear();
    scanf("%d",&n);int cnt=0;
    for(int i = 1; i <= n ; i++){
        int x,y;scanf("%d %d",&x,&y);
        p[cnt].x=x;p[cnt].y=y;p[cnt++].k=1;
    }
    scanf("%d",&m);
    for(int i = 1; i <= m ; i++){
        int x,y;scanf("%d %d",&x,&y);
        p[cnt].x=x,p[cnt].y=y,p[cnt++].k=2;
    }
    sort(p,p+cnt,[](node x,node y){
        if(x.x != y.x)return x.x<y.x;
        return x.y<y.y;
    });
    int ans=1;f[0]=1;
    for(int i = 0 ; i < cnt ; i++){
        int k1=(p[i].x+p[i].y)%H;int k2=(H+(p[i].x-p[i].y)%H)%H;
        if(p[i].k == 2){
            if(f[k1]) f[k1]++;
            if(f[k2]) f[k2]++;
        }
        else{
            f[k1]=f[k2]=max(f[k1],f[k2]);
        }
        ans=max({ans,f[k1],f[k2]});
    }printf("%d\n",ans-1);
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    int t;scanf("%d",&t);
    while(t--){
        solve();
    }           
    return 0;
}       
```
```diff
!     📇2021-01-18
```
   
