#ifndef BINARY_SERACH_TREE_H_20181227
#define BINARY_SERACH_TREE_H_20181227

#include "tree.h"

/*
 * @brief: 找到二叉搜索树中值最小的结点
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    NULL: 根结点为NULL
 *    else: 值最小的结点指针
 */
BSTree *find_min(BSTree *t);

/*
 * @brief: 找到二叉搜索树中值最大的结点
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    NULL: 根结点为NULL
 *    else: 值最大的结点指针
 */
BSTree *find_max(BSTree *t);

/*
 * @brief: 找到二叉搜索树中值为特定值的结点
 * @params:
 *    int value: 指定的键值
 *    BSTree *t: 根结点
 * @return:
 *    NULL: 根结点为NULL或者不存在改值的结点
 *    else: 二叉搜索树中值为elem的结点指针
 */
BSTree *find(int value, BSTree *t);

/*
 * @brief: 在二叉搜索树中插入特定值的结点
 * @params:
 *    int value: 指定的值
 *    BSTree *t: 根结点
 * @return: 插入新结点后的根结点
 */
BSTree *bst_insert(int value, BSTree *t);

/*
 * @brief: 删除二叉搜索树中值为特定值的结点
 * @params:
 *    int value: 指定的键值
 *    BSTree *t: 根结点
 * @return: 返回删除改结点后的根结点
 */
BSTree *bst_delete(int value, BSTree *t);

#endif // !BINARY_SERACH_TREE_H_20181227
