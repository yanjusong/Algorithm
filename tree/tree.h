#ifndef TREE_H_20181227
#define TREE_H_20181227

typedef struct BSTree BSTree;
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

struct BSTree
{
    BSTree *left, *right;
    int element;
    int height;

    BSTree *parent;
    Color color;
};

#define UNUSED(x) (void)x;

/*
 * @brief: 释放树的空间
 * @params:
 *    BSTree *t: 根结点
 */
void make_empty(BSTree *t);

/*
 * @brief: 申请树结点，指定值
 * @params:
 *    int value: 指定结点的值
 * @return:
 *    结点指针
 */
BSTree *getNode(int value);

/*
 * @brief: 获取指定结点的祖父结点指针
 * @params:
 *    BSTree *t: 指定结点指针
 * @return:
 *    祖父结点指针，如果没有则为NULL
 */
BSTree *grandparent(BSTree *t);

/*
 * @brief: 获取指定结点的叔父结点指针
 * @params:
 *    BSTree *t: 指定结点指针
 * @return:
 *    叔父结点指针，如果没有则为NULL
 */
BSTree *uncle(BSTree *t);

/*
 * @brief: 获取树的高度
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    树的高度
 */
int height(BSTree *t);

/*
 * @brief: 控制台打印二叉树
 *         打印红黑树时，黑色结点打印为白色，红色结点打印为红色
 * @params:
 *    BSTree *t: 根结点
 */
void print_ascii_tree(BSTree *t);

/*
 * @brief: 检查树的是否符合搜索特性
 *         1. 左孩子结点的值小于根结点的值
 *         2. 右孩子结点的值大于等于根结点的值
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_sorted(BSTree *t);

/*
 * @brief: 检查树是否符合平衡特征
 *         左子树和右子树高度差的绝对值小于或等于1
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_balanced(BSTree *t);

/*
 * @brief: 检查树是否符合红黑树特征
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_rb_tree(BSTree *t);

/*
 * @brief: 获取树从根结点的到叶子的所有路径中黑色结点最多的路径中黑色结点个数
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    黑色结点个数
 */
int get_bnode_num(BSTree *t);

/*
 * @brief: 检查树是否符合从根节点到叶子每条路径的黑色结点数目是否相等
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_rb_black_num(BSTree *t);

/*
 * @brief: 检查树从根节点到叶子每条路径的是否没有相邻的红色结点
 * @params:
 *    BSTree *t: 根结点
 * @return:
 *    0(false): 不符合
 *    1(true):  符合
 */
bool check_rb_red(BSTree *t);

/*
 * @brief: 操作结点
 * @params: 
 *    BSTree *t: 结点
 *    void *udata: 用户数据
 */
typedef void(*UserFunc)(BSTree *t, void *udata);

/*
 * @brief: 遍历
 *    preorder_travel_recur:  递归前序遍历
 *    preorder_travel_stack:  用栈辅助前序遍历
 *    inorder_travel_recur:   递归中序遍历
 *    inorder_travel_stack:   用栈辅助中序遍历
 *    postorder_travel_recur: 递归后序遍历
 *    postorder_travel_stack: 用栈辅助后序遍历
 *    levelorder_trabel:      层次遍历
 * @params:
 *    BSTree *t: 根结点
 *    UserFunc func: 操作结点函数
 *    void *udata: 用户数据
 */

void preorder_travel_recur(BSTree *t, UserFunc func, void *udata);
void preorder_travel_stack(BSTree *t, UserFunc func, void *udata);

void inorder_travel_recur(BSTree *t, UserFunc func, void *udata);
void inorder_travel_stack(BSTree *t, UserFunc func, void *udata);

void postorder_travel_recur(BSTree *t, UserFunc func, void *udata);
void postorder_travel_stack(BSTree *t, UserFunc func, void *udata);

void levelorder_trabel(BSTree *t, UserFunc func, void *udata);

#endif // !TREE_H_20181227
