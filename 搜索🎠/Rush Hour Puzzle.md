🦑[Rush Hour Puzzle](https://codeforces.com/gym/102460)

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
