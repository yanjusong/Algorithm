#ifndef RED_BLACK_TREE_H_201811230
#define RED_BLACK_TREE_H_201811230

#include "tree.h"

// 红黑树特性:
// 1. 每个结点要么红色要么黑色。
// 2. 根节点必须为黑色。
// 3. 叶子结点(NULL)为黑色。
// 4. 红色结点的孩子结点都为黑色。
// 5. 从根结点到叶子结点的所有简单路径包含的黑色结点数目一样。


BTree *rb_ll_rotate(BTree *t);
BTree *rb_rr_rotate(BTree *t);
BTree *rb_lr_rotate(BTree *t);
BTree *rb_rl_rotate(BTree *t);

/*
 * @brief: 在红黑树中插入特定值的结点，并且调整为红黑树特性的树
 * @params:
 *    int value: 指定的值
 *    BTree *t:  根结点
 * @return: 插入新结点后的根结点
 */
BTree *rb_insert(int value, BTree *t);

/*
 * @brief: 删除二叉搜索树中值为特定值的结点，并且调整为红黑树特性的树
 * @params:
 *    int value: 指定的键值
 *    BTree *t:  根结点
 * @return: 返回删除改结点后的根结点
 */
BTree *rb_delete(int value, BTree *t);

#endif // !RED_BLACK_TREE_H_201811230