#ifndef YJS_OPERATE_TREE_H_
#define YJS_OPERATE_TREE_H_

#include "yjs-Node.h"

/*
 * 二叉树的镜像
 * (1) 递归实现
 * (2) 非递归实现
 */
void mirrorTree(Node *root);
void mirrorTreeNotRcs(Node *root);

/*
 * 层次遍历二叉树
 */
void levelTraversal(Node *root);

/*
 * 前序遍历二叉树
 */
void preOrderTraversal(Node *root);
void preOrderTraversalNotRcs(Node *root);

/*
 * 中序遍历二叉树
 */
void inOrderTraversal(Node *root);
void inOrderTraversalNotRcs(Node *root);

/*
 * 后序遍历二叉树
 */
void postOrderTraversal(Node *root);
void postOrderTraversalNotRcs1(Node *root);
void postOrderTraversalNotRcs2(Node *root);

/*
 * 二叉树高度
 */
int treeHeight(Node *root);

#endif // YJS_OPERATE_TREE_H_