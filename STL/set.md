# set

    🏹对于STL总的来说还是用的太少了，总是感觉很生疏，这里总结一下set的用法QWQ。
    
    
    首先set是自带排序的，那么就说明我们可以对其自定义排序(妙啊)。
    
    最基本的我们想要实现对于大小的排序
    
    🗂️我们可以定义一个比较函数
```C++
struct cmp{

    bool operator()(int x,int y){
        return x>y;//这个里面定义排序的标准
    }
};
std::set<int,cmp>s;
```
    其次我们可能要实现更为复杂的东西，这时我们就必须要严苛定义
    
    比如我要存入结构体
```C++
struct node{

    int dist,sum,size,id,fa;
    node(){};
    node(int dist,int sum,int size,int id,int fa):dist(dist),sum(sum),size(size),id(id),fa(fa){};
    friend bool operator<(node x,node y){
        if(x.sum*y.size > y.sum *x.size) return true;
        else if(x.sum*y.size < y.sum*x.size) return false;
        else{
            if(x.id < y.id) return true;
            else if(x.id > y.id) return false;
            else if(x.id == y.id) return false;
        }
    }
}p[maxn];
```
    在定义排序的标准时，一定要明确的规定。尽可能多的去写，让他在排序时能够完全按你的定义去考虑，所以
    如果你觉得存入的明明不是完全一样但是被删除了，那说明你的定义写的不够完整！！！
