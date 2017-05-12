#ifndef YJS_OPERATE_TREE_H_
#define YJS_OPERATE_TREE_H_

#include "yjs-Node.h"

/*
 * 二叉树的镜像
 * (1) 递归实现
 * (2) 非递归实现
 */
void mirrorTree(Node *root);
void mirrorTreeNotRct(Node *root);

void levelTravel(Node *root);

#endif // YJS_OPERATE_TREE_H_