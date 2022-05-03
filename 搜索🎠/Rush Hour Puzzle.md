 <span id="jump0"></span>
 # [Rush Hour Puzzle](#jump1)
 # [G.The Treasure of the Sierra Jade](#jump2)
<br>
<br>
<br>
 <span id="jump1"></span> 
 
 [<我再查一下>](#jump0)    
 
#  🦑[Rush Hour Puzzle](https://codeforces.com/gym/102460)

    这是一道`迭代加深`的类型题。
    迭代加深其实就是dfs的一种优化，只对于一部题。
    有的时候我们答案可能在很浅的几层里面，dfs会将一颗子树跑到底再去跑另一棵树，这样就会使得浪费了很多时间。
    于是迭代加深通过控制深搜的层数，当搜完规定的所有层数没有答案时，我们再使层数加深，再从头开始搜索，虽然这样会使得前几层重复的搜索，
    但是对于答案在前几层的优化是十分可观的，并且树的结构使我们知道，越往下搜索的会越多，重复前几层带来的后果并不大。
    同时这些题都会一些很明前的字眼：如果在几步之内不能成功就视为失败。。。。。也就说明了答案是有限的
    
    这道题学习了一下某位博主的写法，真的太强了，很多很好的处理技巧。
    
    首先需要决定的使怎么控制小车的方向。
    这里我们每一次都使当前的方块为一辆小车的车尾时在做决定，因为不同车的长度不同，如果每次都让找到一块车的块数就进行操作的话就会
    使得每次dfs的决策种类几乎为30*2,到那时对于一辆小车，只要是他的车身的一块，我们处理一块就可以了，效果是相同的，这样又因为
    不超过10辆车，所以每次决策的种类为10*2,同时我们判断方向也会更加好判断(对于一种车只有两种前进方向)，我们在想他像一个方向前进时，
    我们只需让车尾向前前进 车身-1 的距离，如果这个变到了车头的话那么就说明这是车位，同时这也代表了正确前进方向。
    
```C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <vector>
#include <map>
#include <bitset>

using namespace std;
typedef long long ll;
const int maxn = 10,N = 5e2+10;

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int a[10][10],len[20];
bool vis[10][10];

bool check(int x,int y){if(x >= 1 && x <= 6 && y >= 1 && y <= 6) return true;return false;}

int dfs_len(int x,int y,int k){

    int ans=1;
    vis[x][y]=true;
    for(int i = 0 ; i < 4 ; i++){
        x+=dx[i];y+=dy[i];
        if(check(x,y) && !vis[x][y] && a[x][y] == k){
            ans+=dfs_len(x,y,k);
        }
    }return ans;
}

int get_Min(){

    for(int i = 1; i <= 6 ; i++){
        if(a[3][i] == 1) return 7-i;
    }return 0;
}
bool dfs(int Max,int cur){

    int opt = get_Min();
    if(opt + cur > Max) return false;
    if(opt <= len[1])   return true;
    for(int i = 1; i <= 6 ; i++){
        for(int j = 1; j <= 6 ; j++){

                if(a[i][j]){
                    int xx=i,yy=j,opt=a[i][j];
                    for(int k = 0 ; k < 4 ; k++){

                        int hx=xx+dx[k]*(len[opt]-1),hy=yy+dy[k]*(len[opt]-1);
                        int now_x=xx+dx[k]*len[opt],now_y=yy+dy[k]*len[opt];

                        if(check(hx,hy) && a[hx][hy] == opt){

                            if(check(now_x,now_y) && a[now_x][now_y] == 0){
                                a[now_x][now_y]=opt;
                                a[xx][yy]=0;
                                if(dfs(Max,cur+1)) return true;
                                a[now_x][now_y]=0;
                                a[xx][yy]=opt;
                            }
                        }   
                    }
                }
        }
    }return false;
}
int main()
{
#ifndef ONLINE_JUDGE
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    for(int i = 1; i <= 6 ; i++){
        for(int j = 1; j <= 6 ; j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i = 1; i <= 6 ; i++){
        for(int j = 1; j <= 6 ; j++){
            if(a[i][j] && !vis[i][j]){
                len[a[i][j]]=dfs_len(i,j,a[i][j]);
            }
        }
    }
    for(int i = 1; i <= 10 ; i++){
        if(dfs(i,0)){
            printf("%d\n",i);return 0;
        }
    }printf("-1\n");
    return 0;
}
```
```diff
!     ⏰2021-01-15
```
<br>
<br>
<br>

  [我再查一下](#jump0)
  
   <span id="jump2"></span>
   
 #  [G.The Treasure of the Sierra Jade](https://codeforces.com/gym/103443/problem/G)
![image](https://user-images.githubusercontent.com/92497177/166499394-b47b50dd-df2f-4c8b-9530-57bd76525994.png)


   szgnb!!!!
   真的一下子就猜出了正确思路！！！
   一开始是考虑向某一个方向转移的时候模一下时间看一下是否可以通过，但是我一直不知道zyz是怎么
   保证其不会死循环的，这里正是这道题真正的出现思路的地方。
   
   szg想的正是将所有的数求一下他们的最小公倍数。
   那么我们就建立了一个3维的地图，每一次我们都会往上面一层走一下，到头了再下来，这个是模的概念，当我们把整个
   地图都走完了还没有到达的话就说明不可达。
   为什么是正确的呢？
   
   加入我们考虑一个被所有的士兵都被走过的点，那么所有士兵走一轮的时间就是其所有的最小公倍数lcm，
   如果在这个时间内我们还是呆在原地的话就说明我们一定走不出去了，相同的道理，我们会在每一格最多停留lcm下，
   而如果又走到了这个点就是普通的bfs抵达不到的思想了。
   
   所以就是开了3维的地图，然后每一次穿一层，仍然是bfs的思想。
   
   
ACcode:
```C++
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int dp[41][41][841];
int dx[5] = {0, 0, 0, 1, -1};
int dy[5] = {0, 1, -1, 0, 0};

struct node{
    int x, y, cnt;
};


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int t;  scanf("%d",&t);
    while(t--){
        
        memset(dp, 0, sizeof dp);
        int n, m; scanf("%d %d",&n,&m);  
        vector<vector<int>> a(n, vector<int>(m, 0));
        for(int j = 0 ; j < m ; j++)
            for(int i = 0 ; i < n ; i++)
                cin >> a[i][j];

        int sx, sy;  scanf("%d %d",&sx, &sy);
        int num, d = 1;  scanf("%d",&num);
        vector<pair<int,int> >gd[num];
        for(int i = 0; i < num ; i++){
            int sizes;  scanf("%d",&sizes);
            for(int j = 0 ; j < sizes ; j++){
                int x,y;  scanf("%d %d",&x, &y);
                gd[i].push_back({x, y});
            }
            d = d * sizes / __gcd(d, sizes);
        }

        for(int i = 0 ; i < num; i++){
            for(int time = 0 ; time < d ; time ++){
                int id = time % (int)gd[i].size();
                dp[gd[i][id].first][gd[i][id].second][time] = dp[gd[i][id].first][gd[i][id].second][(time + 1) % d] = -1; 
            }
        }   

        queue<node> q;
        q.push({sx, sy, 0});
        dp[sx][sy][0] = 1;
        int ans = -1;
        while(!q.empty()){
            node u = q.front(); q.pop();

            if(a[u.x][u.y] == 0){
                ans = u.cnt;
                break;
            }
            for(int i = 0 ; i < 5 ; i++){
                int tx = u.x + dx[i];
                int ty = u.y + dy[i];
                if(tx < 0 || tx >= n || ty < 0 || ty >= m || a[tx][ty] > a[u.x][u.y] || dp[tx][ty][(u.cnt + 1) % d] != 0) continue;
                
                q.push({tx, ty, u.cnt + 1});
                dp[tx][ty][(u.cnt + 1) % d] = 1;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}


```

```diff
!   2022-05-04🦟
```
   
