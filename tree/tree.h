#ifndef TREE_H_20181227
#define TREE_H_20181227

typedef struct BTree BTree;

struct BTree
{
    BTree *left, *right;
    int element;
};

BTree *make_empty(BTree *t);

BTree *getNode(int value);

int height(BTree *t);

void print_ascii_tree(BTree *t);

#endif // !TREE_H_20181227
