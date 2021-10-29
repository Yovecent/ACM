##  最小生成树之 kruskal算法

    这里对于kruskal算法进行一些证明，首先我们设T是由kruskal算法求得的一个最小生成树，U是一个最小生成树，然后如果T == U（每一条边），
    那么就可以说其是正确的，但一个图的最小生成树可能不只有一个，然后我们证明一下两棵树的边不完全相同的情况。
    
    🩹我们从T中挑出一个最小的属于T但不属于U的边e，(1)那就是说明，小于e的边没有被选的原因是它存在于U中，然后我们将它加入到U中，
    那么此时U一定构成了一个环因为有了n条边，然后我们从这构成的环中挑出一个不存在于T的边f，这是一定存在的，因为T中本没有环，
    就相当于这个换没有构成的原因，至少是U与T的图中两个都只缺一条边，而这条边不在本图中却在另一个图中。
    
    然后我们就考虑着两条边的权重。
    
    🥖首先如果e == f恒成立，那么我们通过K次交换，现在构成的U就成功便成了T,也就证明了他们相等。
    
    🔡然后如果e < f，那么我们现在构成的U的权重和会更小，那就与U本来是最小生成树不符合，所以不会出现这种情况。
    
    ☣️最后就是当 e > f 的时候，我们挑出的f是因为它不存在于T中，但f的权重比e小却没与被选的原因是，f会与T中已经先出的边(边权小于f)构成环，
    但依据(1)所述，根据小于e的边都存在于U中，而f < e那么小于f的边也一定都在U中，但在U中本没有环所以这是不成立的
    
    
    综上所述，只会出现交换边权相等的情况，这样他们的总权重永不会改变，这就证明了他们都是正确的最小生成树。


🥑然后是对于Kruskal算法的模板
```C++
    struct node{

        int x,y,ans;
        friend bool operator<(node x,node y){
            return x.ans > y.ans;
        }
    }p[maxn<<1];
    int fa[maxn],n,m,Max;

    int find_fa(int x){

        return fa[x] == x ?  x : fa[x] = find_fa(fa[x]);
    }
    void kruskal1(){

        sort(p+1,p+m+1);//将边降序排列
        Max=0;int cnt=0;
        for(int i = 1; i <= n ; i++) fa[i]=i;
        for(int i = 1; i <= m ; i++){
            int x=find_fa(p[i].x);//使用并查集防止成环
            int y=find_fa(p[i].y);
            if(x != y){
                fa[x]=y;
                cnt++;
                Max=max(Max,p[i].ans);
                if(cnt==n-1) return;
            }
        }
     
    }
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= m ; i++){
        scanf("%d %d %d",&p[i].x,&p[i].y,&p[i].ans);
    }
```
[天气晴朗的魔法](https://vjudge.net/contest/449748#problem/D)

    对于这道题，其思路是先生成一颗最小生成树，然后我们就可以确定出来构成树的边权中任意边权
    的最小值，因为我们之前已经证明过，其所构成的多颗最小生成树只是一些相同值的边不一样，所以
    假设我们构成的树的边权是1,3,5的存在构成的一棵树是3,3,3(即会使最大的边权值更小)，那就说明
    我们构成的这个最小生成树并不是真正的最小生成树。
    所以我们也就得出了一个重要的结论，最小生成树是构成的所有树中最大边权值最小的。
    于是我们跑一边最小生成树，找出最大的边权，然后在根据这个上线找出最大生成树，就是答案了。
```C++
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5+10;

struct node{

    int x,y,ans;
    friend bool operator<(node x,node y){
        return x.ans < y.ans;
    }
}p[maxn<<1];
int fa[maxn],n,m,Max;

int find_fa(int x){

    return fa[x] == x ?  x : fa[x] = find_fa(fa[x]);
}
void kruskal1(){

    sort(p+1,p+m+1);
    Max=0;int cnt=0;
    for(int i = 1; i <= n ; i++) fa[i]=i;
    for(int i = 1; i <= m ; i++){
        int x=find_fa(p[i].x);
        int y=find_fa(p[i].y);
        if(x != y){
            fa[x]=y;
            cnt++;
            Max=max(Max,p[i].ans);
            if(cnt==n-1) return;
        }
    }
}
ll kruskal2(){

    sort(p+1,p+m+1,[](node x,node y){
        return x.ans>y.ans;
    });
    int cnt=0;ll sum=0;
    for(int i = 1; i <= n ; i++) fa[i]=i;
    for(int i = 1; i <= m ; i++){
        if(p[i].ans > Max) continue;
        int x=find_fa(p[i].x);
        int y=find_fa(p[i].y);
        if(x != y){
            fa[x]=y;
            cnt++;
            sum+=1ll*p[i].ans;
            if(cnt == n-1) return sum;
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    scanf("%d %d",&n,&m);
    for(int i = 1; i <= m ; i++){
        scanf("%d %d %d",&p[i].x,&p[i].y,&p[i].ans);
    }   
    kruskal1();
    ll ans=kruskal2();
    printf("%lld\n",ans);
    return 0;
}
```

