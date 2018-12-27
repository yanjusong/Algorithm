#ifndef BINARY_SERACH_TREE_H_20181227
#define BINARY_SERACH_TREE_H_20181227

#include "tree.h"

/*
 * @brief: 找到二叉搜索树中值最小的结点
 * @params:
 *    Tree *t: 根结点
 * @return:
 *    NULL: 根结点为NULL
 *    else: 值最小的结点指针
 */
Tree *find_min(Tree *t);

/*
 * @brief: 找到二叉搜索树中值最大的结点
 * @params:
 *    Tree *t: 根结点
 * @return:
 *    NULL: 根结点为NULL
 *    else: 值最大的结点指针
 */
Tree *find_max(Tree *t);

/*
 * @brief: 找到二叉搜索树中值为特定值的结点
 * @params:
 *    int value: 指定的键值
 *    Tree *t:   根结点
 * @return:
 *    NULL: 根结点为NULL或者不存在改值的结点
 *    else: 二叉搜索树中值为elem的结点指针
 */
Tree *find(int value, Tree *t);

/*
 * @brief: 在二叉搜索树中插入特定值的结点
 * @params:
 *    int value: 指定的值
 *    Tree *t:   根结点
 * @return: 插入新结点后的根结点
 */
Tree *insert(int value, Tree *t);

/*
 * @brief: 删除二叉搜索树中值为特定值的结点
 * @params:
 *    int value: 指定的键值
 *    Tree *t:   根结点
 * @return: 返回删除改结点后的根结点
 */
Tree *del(int value, Tree *t);

#endif // !BINARY_SERACH_TREE_H_20181227
