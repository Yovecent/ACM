# ☣️[ST表](https://zhuanlan.zhihu.com/p/105439034)

    ST表的预处理复杂度为O(nlogn)，而每次查询时间为O(1)。
    但缺点是其是离线的，及不能便查询便更新。
    
###  1.ST表的建立
    ST表就是利用了倍增，st[i][j]表示从[i ，i + 2^j - 1]这个区间的Max,Min值。
    建立方法和即为普通倍增，
    即st[i][j] = st[i][j - 1] ? st[i + (1 << (j - 1))][j - 1]
    
    同时外层为跳数，内层为遍历所有编号。
```C++
void build(){

    int k = 32 - __builtin_clz(n) - 1;
    for(int i = 1; i <= n ; i++) info[i][0] = Ro[i] - Lo[i];
    for(int j = 1; j <= k ; j++){
        for(int i = 1; i  + (1 << j) - 1 <= n ; i++){
            info[i][j] = min(info[i][j - 1],info[i + (1 << (j - 1))][j - 1]);
        }
    }
}
```
    
### 2.ST表的查询

    查询时我们只需要找出两个区间，并且让这个区间完全覆盖查询区间即可。
    所以令 l + 2^s - 1 = r
    所以s = log(r - l + 1)即(r - l + 1)所得向下取整，
    
    这里我们可以直接使用__builtin函数
    __builtin_clz(x) 会返回这个整数有多少个前导0
    那么 32 - __builtin_clz(r - l + 1) - 1即为向下取整。
    
    同时在于处理时，我们为了让其尽可能的覆盖1 - n
    所以我们此时的l = 1, r = n
    那么 l + 2^k - 1 = n
    所以我们最大的k即为 log(n)向下取整，即为上述方法。
```C++
int query(int l,int r){

    int k = 32 - __builtin_clz(r - l + 1) - 1;
    return min(info[l][k],info[r - (1 << k) + 1][k]);
}
```
