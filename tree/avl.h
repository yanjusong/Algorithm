#ifndef AVL_TREE_H_201812228
#define AVL_TREE_H_201812228

#include "tree.h"

BTree *avl_ll_rotate(BTree *t);
BTree *avl_rr_rotate(BTree *t);
BTree *avl_lr_rotate(BTree *t);
BTree *avl_rl_rotate(BTree *t);

/*
 * @brief: 在二叉搜索树中插入特定值的结点，并且调整为平衡状态
 * @params:
 *    int value: 指定的值
 *    BTree *t:  根结点
 * @return: 插入新结点后的根结点
 */
BTree *avl_insert(int value, BTree *t);

/*
 * @brief: 删除二叉搜索树中值为特定值的结点，并且调整为平衡状态
 * @params:
 *    int value: 指定的键值
 *    BTree *t:  根结点
 * @return: 返回删除改结点后的根结点
 */
BTree *avl_delete(int value, BTree *t);

#endif // !AVL_TREE_H_201812228
