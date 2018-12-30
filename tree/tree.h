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
    None = 0,
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
 * @brief: 获取指定结点的祖父结点指针
 * @params:
 *    BTree *t: 指定结点指针
 * @return:
 *    祖父结点指针，如果没有则为NULL
 */
BTree *grandparent(BTree *t);

/*
 * @brief: 获取指定结点的叔父结点指针
 * @params:
 *    BTree *t: 指定结点指针
 * @return:
 *    叔父结点指针，如果没有则为NULL
 */
BTree *uncle(BTree *t);

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
 *         打印红黑树时，黑色结点打印为白色，红色结点打印为红色
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

/*
 * @brief: 检查树是否符合红黑树特征
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_rb_tree(BTree *t);

/*
 * @brief: 获取树从根结点的到叶子的所有路径中黑色结点最多的路径中黑色结点个数
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    黑色结点个数
 */
int get_bnode_num(BTree *t);

/*
 * @brief: 检查树是否符合从根节点到叶子每条路径的黑色结点数目是否相等
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_rb_black_num(BTree *t);

/*
 * @brief: 检查树从根节点到叶子每条路径的是否没有相邻的红色结点
 * @params:
 *    BTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_rb_red(BTree *t);

#endif // !TREE_H_20181227
