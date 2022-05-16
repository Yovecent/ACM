🥡Vector
=== 
    🚼之前不怎么用现在是感受到了他的方便了。
    因为可以动态的设置大小，而使的其相比于数组有着得天独厚的优势。

常用总结：
===

## (1) 初始化声明 

    🏹 一维vector:
```C++
    vector<int>v(size,value);
```
    🏹二维vector
```C++
    vector<vector<int>> v(row,vector<int>(col,value);
```

## (2)清除内存

    对于vector的大小的显示我们较多的使用的是size，这个表示了当前vector内我们存下了多少个数，而还有一个capacity。
    
    size:存储的元素的个数
    capacity:预留出来的可以存下的元素的容量
    
    对于vector其会先申请一些内存，对于capacity就是我们预申请的，如果我们想要存储的数量超过了，他就会重新分配内存，
    并且将capacity增大。
    
    所以我们使用clear()时，只会将size变为0，但是我们的申请的内存也就是capacity的值没有变，此时内存并没有被释放，
    只是清了一下vector。
    
    而如果想要释放内存的话，有以下两种方法：

```C++
  
    vector<int>vec, zero;   
       
    //使用shrink_to_fit()将其释放到合适的内存0  
	vec.clear();
	vec.shrink_to_fit();
	
	//交换vec与zero的指针使得他们的值交换
	vec.clear();
	vec.swap(zero);
```
