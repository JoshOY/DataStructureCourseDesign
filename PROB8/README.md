#克鲁斯卡尔（Kruskal）算法  by JoshOY 2014/11/30

##关于最小生成树
所谓最小生成树，通俗地讲就是从图中某点出发，连接所有其他的点的最小距离和的连接方法。
比如本题中就是所谓的“最省钱”的连接方法。
但生成树其实还有其他用途，例如计算机网络中用于避免出现回环，防止出现网络瘫痪。

##关于最小生成树算法(Prim Algorithm)
Prim算法与Kruskal算法是寻找最小生成树的经典方法，两者皆为贪心法，通常使用二元堆积，时间复杂度为 O(E\lg V)。若使用斐波那契堆，Prim算法可加速至 O(E + V\lg V)。

这里由于不使用Prim算法，所以就不多讲了。
可参考[维基百科][1]。

要说二者的区别，Prim算法“专注于节点”，Kruskal算法“专注于边”。
普利姆算法更适用于稠密图（点少边多），克鲁斯卡尔算法更适用于稀疏图（点多边少）。

##克鲁斯卡尔算法的步骤
> * 新建图G，G中拥有原图中相同的节点，但没有边
> * 将原图中所有的边按权值从小到大排序
> * 从权值最小的边开始，如果这条边连接的两个节点于图G中不在同一个连通分量中，则添加这条边到图G中
> * 重复上一步骤，直至图G中所有的节点都在同一个连通分量中

时间复杂度：$$O(E) = E log_2 E(E为图中的边数)$$ 
算法：
```
KRUSKAL-FUNCTION(G, w)
F := 空集合
for each 图 G 中的顶点 v
    do 將 v 加入森林 F
所有的边(u, v) ∈ E依权重 w 递增排序
for each 边(u, v) ∈ E
    do if u 和 v 不在同一棵子树
         then F := F ∪ {(u, v)}
             將 u 和 v 所在的子树合并
```
![GIF描述][2]


  [1]: http://zh.wikipedia.org/wiki/%E6%99%AE%E6%9E%97%E5%A7%86%E7%AE%97%E6%B3%95
  [2]: http://upload.wikimedia.org/wikipedia/commons/5/5c/MST_kruskal_en.gif