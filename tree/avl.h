#ifndef AVL_TREE_H_201812228
#define AVL_TREE_H_201812228

#include "tree.h"

BTree *ll_rotate(BTree *t);
BTree *rr_rotate(BTree *t);
BTree *lr_rotate(BTree *t);
BTree *rl_rotate(BTree *t);

BTree *avl_insert(int value, BTree *t);
BTree *avl_delete(int value, BTree *t);

#endif // !AVL_TREE_H_201812228
