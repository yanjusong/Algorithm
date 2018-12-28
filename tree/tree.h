#ifndef TREE_H_20181227
#define TREE_H_20181227

typedef struct BTree BTree;

struct BTree
{
    BTree *left, *right;
    int element;
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

#endif // !TREE_H_20181227
