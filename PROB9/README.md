#红黑树 by JoshOY  2014/11/25
##需求
项目简介：
依次输入关键字并建立二叉排序树，实现二叉排序数的插入和查找功能。

项目功能简介：
二叉排序树就是指将原来已有的数据根据大小构成一棵二叉树，二叉树中的所有结点数据满足一定的大小关系，所有的左子树中的结点均比根结点小，所有的右子树的结点均比根结点大。
二叉排序树查找是指按照二叉排序树中结点的关系进行查找，查找关键自首先同根结点进行比较，如果相等则查找成功；如果比根节点小，则在左子树中查找；如果比根结点大，则在右子树中进行查找。这种查找方法可以快速缩小查找范围，大大减少查找关键的比较次数，从而提高查找的效率。

##关于红黑树
红黑树实际上就是一种平衡二叉树。

它有五个属性：key, parent, left, right, color
其中color只有两种：Red, Black
并且规定：树中两个连接的节点<strong>不能</strong>同时为红色。

与AVL树的不同点在于，AVL树使用的是平衡因子来确定何时应该旋转，
而红黑树是通过红黑色来确定何时应该旋转。

二者相比，插入、搜索、删除的最坏情况时间复杂度都是O(log n)。

引入二叉树的目的是为了提高二叉树的搜索的效率，减少树的平均搜索长度。为此，就必须每向二叉树插入一个结点时调整树的结构，
使得二叉树搜索保持平衡，从而可能降低树的高度，减少的平均树的搜索长度。

红黑树是牺牲了严格的高度平衡的优越条件为代价，使得自身能够以O(log n)的时间复杂度进行搜索、插入、删除操作。
此外，由于它的设计，任何不平衡都会在三次旋转之内解决。红黑树的算法时间复杂度和AVL相同，但统计性能比AVL树更高。

##实现红黑树
由于需求上没说删除（外加红黑树的删除节点实在太BT，情况多到爆），所以完成了搜索、插入功能。

首先从节点开始：

	template <class T>
	struct RBTNode {
		RBTNode(RBTNode* _pNode)
		{
			this->color = RBT_RED;
			this->parent = _pNode;
			this->left = nullptr;
			this->right = nullptr;
		}
	
		RBTNode(RBTNode* _pNode, const T& _key)
		{
			this->color = RBT_RED;
			this->parent = _pNode;
			this->left = nullptr;
			this->right = nullptr;
			this->key = _key;
		}
		T key;
		RBColor color;
		RBTNode *parent;
		RBTNode *left;
		RBTNode *right;
	};

这个不多说。请参照红黑树节点的基本定义。其中，RBColor是一个布尔值(typedef bool RBColor;)，默认生成的新节点为红色。

注意，要自己生成一个nil节点！
nil节点是一个“空节点”，但它和nullptr不同，他虽然“空”但有Color属性，而且永远是黑色。这点如何证明？可以参看《算法导论》第十三章中的一道习题。

然后是树，由于太长了请直接看RedBlackTree.h中的class RBTree，代码就不放了。

其中要提一下的是树的左旋和右旋，这里只给出左旋的代码，注意交换节点的顺序，别弄错了：

	void leftRotate(RBTNode<T> *x)
	{
		RBTNode<T> *y = x->right;	// y为x的右节点
		x->right = y->left;
		if (y->left != this->nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == this->nil)	// 若x的父节点为根节点，要记得更新树的根节点
			this->root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}


右旋“同理可得”。具体的细节可以参看《算法导论》第十三章，旋转会改变树的节点位置关系，但偏序关系不发生改变。
也就是说，通过旋转，我们可以降低树的高度但不改变树中的节点之间的偏序关系（即“大小”关系）。

插入：
插入新节点时，新节点是红色的。
我们先按照一般二叉树的方式进行插入：

	void insert(const T& value)
	{
		RBTNode<T> *y = this->nil;
		RBTNode<T> *x = this->root;
		RBTNode<T> *z = nullptr;
	
		while (x != this->nil) {
			y = x;
			if (value < x->key)
				x = x->left;
			else
				x = x->right;
		}
	
		z = new RBTNode<T>(y, value);
	
		if (y == this->nil)
			this->root = z;
		else if (value < y->key)
			y->left = z;
		else
			y->right = z;
	
		z->left = this->nil;
		z->right = this->nil;
		z->color = RBT_RED;
		
		insertFixup(z);
		return;
	}

注意倒数第二行的insertFixup(z);
这是唯一一句和一般搜索树插入不同的地方。
也就是说，好戏来了：

	void insertFixup(RBTNode<T>* z) {
		while (z->parent->color == RBT_RED) {
			if (z->parent == z->parent->parent->left) {
				RBTNode<T>* y = z->parent->parent->right;
				/* Case 1 */
				if (y->color == RBT_RED) {
					z->parent->color = RBT_BLACK;
					y->color = RBT_BLACK;
					z->parent->parent->color = RBT_RED;
					z = z->parent->parent;
					continue;
				}
				/* Case 2 */
				else if (z == z->parent->right) {
					z = z->parent;
					leftRotate(z);	/* Then it turns into case 3 */
				}
				/* Case 3 */
				z->parent->color = RBT_BLACK;
				if (z->parent->parent != nullptr) {
					z->parent->parent->color = RBT_RED;
					rightRotate(z->parent->parent);
				}
			}
			else if (z->parent == z->parent->parent->right) {
				RBTNode<T>* y = z->parent->parent->left;
				/* Case 1 */
				if (y->color == RBT_RED) {
					z->parent->color = RBT_BLACK;
					y->color = RBT_BLACK;
					z->parent->parent->color = RBT_RED;
					z = z->parent->parent;
					continue;
				}
				/* Case 2 */
				else if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);	/* Then it turns into case 3 */
				}
				/* Case 3 */
				z->parent->color = RBT_BLACK;
				if (z->parent->parent != nullptr) {
					z->parent->parent->color = RBT_RED;
					leftRotate(z->parent->parent);
				}
			} /* end if */ 
		} /* end while */
		this->root->color = RBT_BLACK;
	}

其实这是《算法导论》中伪代码的“个人翻译版”，不过原书中的伪代码略带误导性，比如case1之后要continue但伪代码没写，
还有就是case3的后两步要考虑z为根节点时的特殊情况。
（当然，也可能是个人技术水平有限，只能写出这种代码了，晕）
但是case1，case2，case3是什么？
可以参照算法导论中的说明，也可以看<a href="http://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91">维基百科：红黑树</a>。

这三种“不平衡”状态即插入时所有可能的情况，而且情况2可以直接转换为情况3。

至于搜索，没什么说的。和普通二叉树没有区别，但效率远高于普通二叉树（全面碾压）。

##其他想说的
脑子有些累，回头再想吧。
删除功能我会尽快完成的。毕竟不在需求之内啊。
