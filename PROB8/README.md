#克鲁斯卡尔（Kruskal）算法 - by JoshOY 2014/11/30

###关于最小生成树
所谓最小生成树，通俗地讲就是从图中某点出发，连接所有其他的点的最小距离和的连接方法。
比如本题中就是所谓的“最省钱”的连接方法。
但生成树其实还有其他用途，例如计算机网络中用于避免出现回环，防止出现网络瘫痪。

###关于最小生成树算法(Prim Algorithm)
Prim算法与Kruskal算法是寻找最小生成树的经典方法，两者皆为贪心法，通常使用二元堆积，时间复杂度为 O(E\lg V)。若使用斐波那契堆，Prim算法可加速至 O(E + V\lg V)。

这里由于不使用Prim算法，所以就不多讲了。
可参考维基百科：http://zh.wikipedia.org/wiki/%E6%99%AE%E6%9E%97%E5%A7%86%E7%AE%97%E6%B3%95

要说二者的区别，Prim算法“专注于节点”，Kruskal算法“专注于边”。