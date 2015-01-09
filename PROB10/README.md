# 排序算法大杂烩
----------
对十种排序算法做一个总结。

## 目录
1. 冒泡排序
2. 选择排序
3. 直接插入排序
4. 希尔排序
5. 快速排序
6. 堆排序
7. 归并排序
8. 基数排序

## 冒泡排序
比较基础也是最简单的排序算法之一。

主要思想就是：不断遍历数组，如果两个相邻的数据排序顺序不符合偏序关系，就交换他们。

以 n 个整数组成的数组 ls 为例，从小到大排序。当第 i 遍遍历后，一定满足 ls[n - i] 及其后面的元素已排好序。

于是，随着遍历次数的增加，偏序关系较“大”（反之较“小”）的数就会像气泡一样“浮”至数组的首端或尾端。

故名曰：冒泡排序。

```python
def bubble_sort(ls):
    n = len(ls)                                      # n为数组的长度
    while n > 0:                                     # 基本思想就是第i次遍历后保证第i大的元素到正确的位置
        for i in range(n - 1):                       # 同C/C++的 for(int i = 0; i < n - 1; i++) {...}
            if ls[i+1] < ls[i]:                      # 如果ls[i]与ls[i+1]偏序关系不对
                (ls[i], ls[i+1]) = (ls[i+1], ls[i])  # 交换第i个和第i+i个元素
        n -= 1
    return ls
```

很容易看出，有两层循环。总循环次数 n + (n - 1) + (n - 2) + ... + 1 = (n^2 + n) / 2

故时间复杂度为O(n^2)（所以说——该算法慎用或干脆别用~）。

由于没有用到辅助数组之类的玩意，所以空间复杂度为O(1)。

## 选择排序
其思想有些类似于冒泡排序：都是保证第i次遍历后，第i大（或小）的元素排在数组的正确位置。

但是，冒泡是通过遍历不断交换元素位置达到效果的。而选择排序则是记录下第i大（或第i小）元素的位置然后排序的。

也就是说，第 i 次遍历，遍历ls[0] ~ ls[n - i]。 找出其中最大的元素，记录索引值 max_element_index 。即 ls[max_element_index] 是当前 0 ~ (n-i) 号元素中最大的元素。

然后，交换 ls[min_element_index] 和 ls[n - i]，即完成了第i次遍历。然后以此类推……

代码如下：
```python
def selection_sort(ls):
    n = len(ls)                                                               # n为数组长度
    for i in xrange(n - 1, 0, -1):                                            # 同C/C++的for(int i = n-1; i > 0; i--)
        max_element_index = 0                                                 # 初始化最大元素索引值为0
        for j in range(i + 1, len(ls)):                                       # 查找最大的元素的索引值
            if ls[j] > ls[max_element_index]:
                max_element_index = j                                         # 更新最大的元素的索引值
        if max_element_index != i:                                            
            (ls[i], ls[max_element_index]) = (ls[max_element_index], ls[i])   # 交换，完成本次遍历
    return ls
```

同样，两层循环，时间复杂度O(n^2)，但是至多进行n-1次交换，所以选择排序在交换移动元素方面比较优秀。

只用到了一个辅助记录最大（或最小）元素索引值的变量max_element_index。故空间复杂度O(1)。

## 直接插入排序

如果是这么一个情况：我有一个含 i 个元素，已经排好序的数组 arr 。现在，来了一个新的元素 temp， 要把它插入该数组，然后让该数组排好序，怎么办？

最简单的办法就是，既然该数组已经排好序了，那么就从最后一个，也就是最大的那个开始，向前遍历呗。如果遍历到某个元素arr[j]时，发现 arr[j] < temp， 那就让 arr[j] 后面的每个元素向后挪一位。空出一个位置，插入temp。结束。

那么，我们换种想法，假设遍历一个未排序的数组，第 i 次遍历时，认为前 i 个元素已排好。那么 arr[i] （第 i+1 个元素）作为 temp 插入……
然后懂了吧。

在C/C++中，如果采用这种方法，需要一个与数组等长的辅助空间，以防数组越界。

```python
def insertion_sort(ls):
    if len(ls) == 1:                        # 数组长度为1时，还用排？！
        return
 
    for i in xrange(1, len(ls)):            # 按照上面的解释，认为ls[0] ~ ls[i-1] 已经排好序了
        temp = ls[i]                        # 插入元素为 temp， 即ls[i]
        j = i - 1                           # 初始化 j
        while j >= 0 and temp > ls[j]:      # 一直找到比 temp 小的
            ls[j + 1] = ls[j]
            j -= 1
        ls[j + 1] = temp
```

## 希尔排序
希尔排序算是对直接插入排序的一种改版，不过我们需要一个“步长”。
所谓“步长”，简单来说就是：我要将长度为 n 的数组中的元素从头开始分组，相邻的 g 个一组，那么 g 就叫做步长。

这里举个维基百科上的例子，假设数组为：[13 14 94 33 82 25 59 94 65 23 45 27 73 25 39 10]
假设我们确定步长为 5，然后数组就分成了 4 组，每行一组：

```
13 14 94 33 82
25 59 94 65 23
45 27 73 25 39
10
```
注意到这样就形成了**5列**。
每列排序之后：
```
10 14 73 25 23
13 27 94 33 39
25 59 94 65 82
45
```

于是得到数组为：[10 14 73 25 23 13 27 94 33 39 25 59 94 65 82 45]
然后，步长变3,
```
10 14 73
25 23 13
27 94 33
39 25 59
94 65 82
45
```
每列排序之后：
```
10 14 13
25 23 33
27 25 59
39 65 73
45 94 82
94
```
于是得到数组：[10 14 13 25 23 33 27 25 59 39 65 73 45 94 82 94]
最后，调整步长为 1，然后，所有的元素排在一列，于是……请用直接插入排序解决。

程序如下：
```python
def shell_sort(ls):
    gap = int(len(ls) / 2)                  # 开始时默认设步长为数组长度的 1/2
    while gap > 0:                          # 每次循环步长减半，直至步长为1的循环完成后结束
        for i in range(gap, len(ls)):       # 然后对每组看成独立数组，进行直接插入排序，具体原理见直排
            key = ls[i]
            j = i - gap
            while j >= 0 and ls[j] > key:
                ls[j + gap] = ls[j]
                j -= gap
            ls[j + gap] = key               # 直接插入排序部分结束
        gap /= 2                            # 步长减半
    return ls
```
希尔排序的要点就是分组排序，使数组变得较为有序，最后利用“直接插入排序对较为有序的数组进行排序时，耗时较少”这一特点减少耗时。

希尔排序的时间复杂度：根据步长来定，最坏的时间复杂度可能有O(n^2) ~ O(n(logn)^2)。
至于步长怎么选，一般来说就按上面的程序中：以数组长度的一半为开始，然后每次循环减半。
不过貌似还有更好的：详见[维基百科：希尔排序][1]。

## 快速排序
最常用的排序之一，效率通常较高而且好写。
思想就是从数组中找到一个元素pivot作为“基准”，然后后面的所有元素比“基准”大的分为一组left，比“基准”小的分为一组right。（通常来讲嫌麻烦的话我们就会拿第一个元素做基准）
然后，left和right两组用快排递归完成排序。
最后，合成排序后的数组 [left pivot right]。

例如有这么一个数组： [4 8 1 2 0 9 3 7 5 6]
拿第一个元素4作为基准，然后遍历一遍数组。得到比4小的元素数组left: [1 2 0 3]， 比4大的元素数组right: [8 9 7 5 6]。
然后left中以第一个元素1为基准分为： [0]; 1; [2 3]
...
当只有零个或一个元素时就可以返回了。
于是合并得到 [0 1 2 3]

同理，对right以同样的策略得到right: [5 6 7 8 9]
然后 left = [0 1 2 3]; pivot = 4; right = [5 6 7 8 9]
合并得到[0 1 2 3 4 5 6 7 8 9]

```python
def quick_sort(ls):
    if len(sorting_list) == 0:                                # 数组长度为0的情况
        return []
    elif len(sorting_list) == 1:                              # 数组长度为1的情况
        return sorting_list
    else:
        pivot = ls[0]                                         # 开始时设基准为第一个元素
        left = quick_sort([x for x in ls[1:] if x < pivot])   # 挑出小的元素放在一个数组中进行快排
        right = quick_sort([x for x in ls[1:] if x >= pivot]) # 挑出大的元素放在一个数组中进行快排
        return left + [pivot] + right                         # 返回合并后的数组
```
不过由于是python，列表有先天优势。
下面给出C/C++代码，以一个int数组为例：
```C++
void swap(int &A, int &B)                      // 交换函数
{
    A = A ^ B;
    B = A ^ B;
    A = A ^ B;
    return;
}

void quickSort(int *arr, int length)
{
    if (length == 0 || length == 1) {          // 如果数组长度为0或1就返回
        return;
    }
    int pivot = arr[0];                        // 否则，以第一个元素为基准，进行递归
    int head  = 0;
    int tail  = length - 1;
    int i     = 1;
    
    while (head != tail) {
        if (arr[i] > pivot) {
            swap(arr[i], arr[tail]);
            tail--;
        }
        else {
            swap(arr[i], arr[head]);
            head++;
            i++;
        }
    }
    
    arr[head] = pivot;
    quickSort(&arr[0], head + 1);
    quickSort(&arr[head + 1], length - head - 1);
    
    return;
}
```
时间复杂度分析：最快O(nlogn)，也就是说最理想的情况下每次都能刚好以大小次序最中间的元素为基准。
这样就构成了一颗完全二叉树，会非常快。
但最坏时间复杂度就是O(n^2)了。
所以关键问题就出在怎么找基准上。


## 堆排序
堆排序（Heapsort）是指利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的
结构，并同时满足堆积的性质：即子结点的键值或索引总是小于（或者大于）它的父节点。
通常堆是通过一维数组来实现的。在起始数组为 0 的情形中：
父节点i的左子节点在位置 (2 * i + 1);
父节点i的右子节点在位置 (2 * i + 2);
子节点i的父节点在位置 floor((i - 1)/ 2);
```python
def heap_sort(ls):
	def shift_down(start, end):
		root = start
		while True:
			child = 2 * root + 1
		if child > end:
			break
		if child + 1 <= end and ls[child] < ls[child+1]:
			child += 1
		if ls[root] < ls[child]:
			(ls[root], ls[child]) = (ls[child], ls[root])
			root = child
		else:
			break

#create heap
for start in xrange((len(ls)‐2)/2, ‐1, ‐1):
	shift_down(start, len(ls) ‐ 1)

#sort
for end in xrange(len(ls)‐1, 0, ‐1):
	(ls[0], ls[end]) = (ls[end], ls[0])
	shift_down(0, end‐1)
return ls
```

## 归并排序

归并排序（Merge sort）是创建在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide
and Conquer）的一个非常典型的应用。

归并操作的过程如下：

1. 申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
2. 设定两个指针，最初位置分别为两个已经排序序列的起始位置
3. 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
4. 重复步骤3直到某一指针到达序列尾
5. 将另一序列剩下的所有元素直接复制到合并序列尾

```python
def merge_sort(sorting_list):
    global merge_step
    if(len(sorting_list) <= 1):
        return sorting_list
    def merge(left, right):
        global merge_step
        rtn = []
        while len(left) != 0 and len(right) != 0:
            rtn.append(left.pop(0) if left[0] <= right[0] else right.pop(0))
            merge_step += 1
        while len(left) != 0:
            merge_step += 1
            rtn.append(left.pop(0))
        while len(right) != 0:
            merge_step += 1
            rtn.append(right.pop(0))
        return rtn
    ls = copy.deepcopy(sorting_list)
    middle_index = int(len(ls) / 2)
    left = merge_sort(ls[0:middle_index])
    right = merge_sort(ls[middle_index:])
    return merge(left, right)
```

## 基数排序

基数排序（Radix sort）是一种非比较型整数排序算法，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基
数排序也不是只能使用于整数。
它是这样实现的：将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列。
基数排序的方式可以采用LSD（Least significant digital）或MSD（Most significant digital），LSD的排序方式由键值的最右边开始，而MSD则相反，由键值的最左边开始。

```python
import copy

def __getMaxBit(sorting_list):
    d = 1
    p = 10
    for i in sorting_list:
        while i > p:
            d += 1
            p *= 10
    return d

def radix_sort(sorting_list):
    step = 0
    d = __getMaxBit(sorting_list)
    ls = copy.deepcopy(sorting_list)
    tmp = [0] * len(ls)
    radix = 1
    for i in range(d):
        count = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        for j in range(len(ls)):
            k = int(ls[j] / radix) % 10
            count[k] += 1
            step += 1
        for j in range(1, 10):
            count[j] += count[j-1]
        for j in xrange(len(ls)-1, -1, -1):
            k = int(ls[j] / radix) % 10
            tmp[count[k] - 1] = ls[j]
            count[k] -= 1
            step += 1
        for j in range(len(ls)):
            ls[j] = tmp[j]
            step += 1
        radix *= 10
    return (ls, step)


if __name__ == "__main__":
    sList=[13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print(radix_sort(sList))
```


[1]:http://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F