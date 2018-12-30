#ifndef TREE_H_20181227
#define TREE_H_20181227

typedef struct BTree BTree;
typedef enum Color Color;

#ifndef __cplusplus
typedef int bool;
#define false 0
#define true 1
#endif

enum Color
{
    Red = 1,
    Black = 2,
};

struct BTree
{
    BTree *left, *right;
    int element;

    BTree *parent;
    Color color;
};

/*
 * @brief: 释放树的空间
 * @params:
 *    BTree *t: 根结点
 */
void make_empty(BTree *t);

/*
 * @brief: 申请树结点，指定值
 * @params:
 *    int value: 指定结点的值
 * @return:
 *    结点指针
 */
BTree *getNode(int value);

/*
 * @brief: 获取树的高度
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    树的高度
 */
int height(BTree *t);

/*
 * @brief: 控制台打印二叉树
 * @params:
 *    BTree *t: 根结点
 */
void print_ascii_tree(BTree *t);

/*
 * @brief: 检查树的是否符合搜索特性
 *         1. 左孩子结点的值小于根结点的值
 *         2. 右孩子结点的值大于等于根结点的值
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_sorted(BTree *t);

/*
 * @brief: 检查树是否符合平衡特征
 *         左子树和右子树高度差的绝对值小于或等于1
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_balanced(BTree *t);

#endif // !TREE_H_20181227
