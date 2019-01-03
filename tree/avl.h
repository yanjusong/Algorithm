#ifndef AVL_TREE_H_201812228
#define AVL_TREE_H_201812228

#include "tree.h"

BSTree *avl_ll_rotate(BSTree *t);
BSTree *avl_rr_rotate(BSTree *t);
BSTree *avl_lr_rotate(BSTree *t);
BSTree *avl_rl_rotate(BSTree *t);

/*
 * @brief: 在二叉搜索树中插入特定值的结点，并且调整为平衡状态
 * @params:
 *    int value: 指定的值
 *    BSTree *t: 根结点
 * @return: 插入新结点后的根结点
 */
BSTree *avl_insert(int value, BSTree *t);

/*
 * @brief: 删除二叉搜索树中值为特定值的结点，并且调整为平衡状态
 * @params:
 *    int value: 指定的键值
 *    BSTree *t: 根结点
 * @return: 返回删除改结点后的根结点
 */
BSTree *avl_delete(int value, BSTree *t);

#endif // !AVL_TREE_H_201812228
